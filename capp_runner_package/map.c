#include "map.h"

#include <base.h>
#include <graphics.h>

#include "data.h"
#include "global.h"
#include "room.h"

Map *mapCreate(int luck) {
	// 初始化变量
	Map *map = create(sizeof(Map));

	// 创建主房间
	int roomX = 1, roomY = 1;
	int downOrRight = rand() % 2;
	int turnIndex = rand() % 5;
	map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomCreate(map, roomX, roomY, Room_Init);
	for (int i = 0; i < 6; i++) {
		if (i == turnIndex) {
			downOrRight = downOrRight == true ? false : true;
		}
		downOrRight ? roomY++ : roomX++;
		enum RoomType type;
		if (i == 5) {
			type = Room_Boss;
		} else if (i == 4) {
			type = Room_Shop;
		} else {
			type = Room_Battle;
		}
		Room *room = map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomCreate(map, roomX, roomY, type);
		Room *prev = room->prevRoom = map->roomList[map->roomCount - 2];
		room->linkRooms[room->linkRoomCount++] = prev;
		prev->linkRooms[prev->linkRoomCount++] = room;
	}

	// 查找次级房间的位置。
	int slots[100];
	int slotsSuper[100];
	int slotCount = 0;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int type = room->type;
		// printf("%s\n", room->caption);
		if (type == Room_Init || type == Room_Boss || type == Room_Shop) {
			continue;  // 终点的boss房间和商店房间，不连接次级房间。
		}
		int x = room->x;
		int y = room->y;
		if (y > 0) {
			Room *top = map->rooms[y - 1][x];
			if (top == NULL) {
				slots[slotCount++] = x + (y - 1) * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y - 1][x] = roomCreate(map, x, y - 1, Room_Init);
			}
		}
		if (x < 9) {
			Room *right = map->rooms[y][x + 1];
			if (right == NULL) {
				slots[slotCount++] = x + 1 + y * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y][x + 1] = roomCreate(map, x + 1, y, Room_Init);
			}
		}
		if (y < 9) {
			Room *bottom = map->rooms[y + 1][x];
			if (bottom == NULL) {
				slots[slotCount++] = x + (y + 1) * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y + 1][x] = roomCreate(map, x, y + 1, Room_Init);
			}
		}
		if (x > 0) {
			Room *left = map->rooms[y][x - 1];
			if (left == NULL) {
				slots[slotCount++] = x - 1 + y * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y][x - 1] = roomCreate(map, x - 1, y, Room_Init);
			}
		}
	}
	//printf("sc %d\n", slotCount);
	for (int i = 0; i < slotCount; i++) {
		int index = rand() % slotCount;
		int tmp = slots[i];
		int tmpSuper = slotsSuper[i];
		slots[i] = slots[index];
		slots[index] = tmp;
		slotsSuper[i] = slotsSuper[index];
		slotsSuper[index] = tmpSuper;
	}

	// 计算次级房间生成概率比。
	int ratioRanges[5];
	int ratioSum = 0;
	// printf("概率比：");
	for (int i = 0; i < 5; i++) {
		int room_luck = room_gene_data[i].luck;
		if (room_luck >= 0) {
			ratioRanges[i] = luck - room_luck;
		} else {
			ratioRanges[i] = -room_luck;
		}
		if (ratioRanges[i] <= 4) {
			ratioRanges[i] = 4;	 // 最低概率比
		}
		ratioSum += ratioRanges[i];
		// printf("%d ", ratioRanges[i]);
	}
	// printf("\n");
	// printf("总共：%d\n", ratioSum);
	// mapPrint(map);

	// 生成次级房间。
	float remainRoomCount = 4;
	for (int i = 0; i < slotCount; i++) {
		if (remainRoomCount <= 0) {
			break;	// 次级房间数量已足够。
		}
		int x = slots[i] % 10;
		int y = slots[i] / 10;
		Room *slot = map->rooms[y][x];
		if (slot != NULL) {
			continue;  // 主房间的次级房间的位置可能有重叠，如果已创建房间，那么忽略重复位置。
		}
		int ratioRand = rand() % ratioSum;
		int ratioStart = 0;
		int roomGeneIndex = -1;
		for (int j = 0; j < 5; j++) {
			int range = ratioRanges[j];
			if (ratioRand >= ratioStart && ratioRand < ratioStart + range) {
				roomGeneIndex = j;
				break;
			}
			ratioStart += range;
		}
		if (roomGeneIndex > -1) {
			Room *room = map->roomList[map->roomCount++] = map->rooms[y][x] = roomCreate(map, x, y, room_gene_data[roomGeneIndex].type);
			Room *super = room->superRoom = map->roomList[slotsSuper[i]];
			room->linkRooms[room->linkRoomCount++] = super;
			super->linkRooms[super->linkRoomCount++] = room;
			remainRoomCount -= room_gene_data[roomGeneIndex].cost;
		}
	}

	map->currentRoom = map->roomList[0];
	for (int i = 0; i < map->roomCount; i++) {
		roomInitTile(map->roomList[i]);
	}

	return map;
}

void mapDispose(Map *map) {
	for (int i = 0; i < map->roomCount; i++) {
		roomDispose(map->roomList[i]);
	}
	dispose(map);
}

void mapDraw(Map *map, double t) {
	roomDraw(map->currentRoom, t);
}

void mapUpdate(Map *map, double t) {
	roomUpdate(map->currentRoom, t);
}

void mapDrawMiniMap(Map *map, double t) {
	int c = 60;
	int d = 40;
	int doorw = 10;
	int cd = c + d;
	int x0 = 0, y0 = 0;
	int top = 0, right = 0, bottom = 0, left = 0;
	int w = 0, h = 0;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int x = room->x;
		int y = room->y;
		if (i == 0) {
			top = y0 = y;
			right = x;
			bottom = y;
			left = x0 = x;
		} else {
			if (top > y)
				top = y0 = y;
			if (right < x)
				right = x;
			if (bottom < y)
				bottom = y;
			if (left > x)
				left = x0 = x;
		}
	}
	w = (right + 1 - left) * cd - d;
	h = (bottom + 1 - top) * cd - d;
	x0 = (SCRW - w) / 2 - x0 * cd;
	y0 = (SCRH - h) / 2 - y0 * cd;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int x = x0 + room->x * cd;
		int y = y0 + room->y * cd;
		int32 bcolor = 0x99aa9933;
		int32 bgcolor = 0xaa336699;
		int32 linkColor = 0x99aa9933;
		// printf("[%s, %d,%d]\n", room->caption, x, y);
		if (map->currentRoom == room) {
			bcolor = 0xffaa9933;
			bgcolor = 0xff336699;
			linkColor = 0xffaa9933;
		}
		drawRect(x, y, c, 3, bcolor);
		drawRect(x + c - 3, y, 3, c, bcolor);
		drawRect(x, y + c - 3, c, 3, bcolor);
		drawRect(x, y, 3, c, bcolor);
		drawRect(x + 3, y + 3, c - 6, c - 6, bgcolor);
		switch (room->type) {
		case Room_Boss:
			drawTextC(room->caption, x, y, c, c, 245, 60, 60, 30);
			break;
		default:
			drawTextC(room->caption, x, y, c, c, 235, 235, 60, 30);
			break;
		}

		Room *linkRoom = room->prevRoom;
		if (linkRoom == NULL) {
			linkRoom = room->superRoom;
		}
		if (linkRoom != NULL) {
			if (room->x == linkRoom->x) {
				if (room->y > linkRoom->y) {
					drawRect(x + (c - doorw) / 2, y - d, doorw, d, linkColor);
				} else {
					drawRect(x + (c - doorw) / 2, y + c, doorw, d, linkColor);
				}
			} else if (room->y == linkRoom->y) {
				if (room->x > linkRoom->x) {
					drawRect(x - d, y + (c - doorw) / 2, d, doorw, linkColor);
				} else {
					drawRect(x + c, y + (c - doorw) / 2, d, doorw, linkColor);
				}
			}
		}
	}
}