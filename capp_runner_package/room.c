#include "room.h"

#include "base.h"
#include "global.h"
#include "map.h"

RoomTile *roomTileCreate(int x, int y, int w, int h, enum RoomTileType type) {
	RoomTile *tile = malloc(sizeof(RoomTile));
	memset(tile, 0, sizeof(RoomTile));
	tile->x = x;
	tile->y = y;
	tile->w = w;
	tile->h = h;
	tile->type = type;
	return tile;
}

Room *roomCreate(Map *map, int x, int y, enum RoomType type) {
	Room *room = malloc(sizeof(Room));
	memset(room, 0, sizeof(Room));
	room->map = map;
	room->x = x;
	room->y = y;
	room->w = 10;
	room->h = 10;
	room->type = type;
	switch (type) {
	case Room_Init:
		room->caption = utf8_c("初");
		break;
	case Room_Battle:
		room->caption = utf8_c("战");
		break;
	case Room_Trap:
		room->caption = utf8_c("阵");
		break;
	case Room_Potions:
		room->caption = utf8_c("釜");
		break;
	case Room_Treasure:
		room->caption = utf8_c("箱");
		break;
	case Room_Elite:
		room->caption = utf8_c("魂");
		break;
	case Room_Shop:
		room->caption = utf8_c("店");
		break;
	case Room_Boss:
		room->caption = utf8_c("狱");
		break;
	default:
		room->caption = utf8_c("");
		break;
	}
	float roomW = 500;	// 房间x宽度
	float roomH = 500;	// 房间y宽度
	room->px = (SCRW - roomW) / 2;
	room->py = (SCRH - roomH) / 2;
	return room;
}

void roomInitTile(Room *room) {
	float roomW = 500;	// 房间x宽度
	float roomH = 500;	// 房间y宽度
	float wallD = 30;	// 墙壁厚度
	float doorW = 80;	// 门宽度
	// 地板
	RoomTile *floor = roomTileCreate(wallD, wallD, roomW, roomH, RoomTile_Floor);
	floor->caption = room->caption;
	room->tiles[room->tileCount++] = floor;
	// 墙壁
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, roomW + wallD * 2, wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(roomW + wallD, 0, wallD, roomH + wallD * 2, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(0, roomH + wallD, roomW + wallD * 2, wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, wallD, roomH + wallD * 2, RoomTile_Wall);
	// 门
	for (int i = 0; i < room->linkRoomCount; i++) {
		Room *linkRoom = room->linkRooms[i];
		RoomTile *tile = NULL;
		if (room->x == linkRoom->x) {
			if (room->y > linkRoom->y) {  // 上
				tile = roomTileCreate(wallD + roomW / 2 - doorW / 2, 0, doorW, wallD, RoomTile_Door);
				tile->doorDirection = 2;
			} else {  // 下
				tile = roomTileCreate(wallD + roomW / 2 - doorW / 2, roomH + wallD, doorW, wallD, RoomTile_Door);
				tile->doorDirection = 8;
			}
		} else if (room->y == linkRoom->y) {
			if (room->x > linkRoom->x) {  // 左
				tile = roomTileCreate(0, wallD + roomH / 2 - doorW / 2, wallD, doorW, RoomTile_Door);
				tile->doorDirection = 4;
			} else {  // 右
				tile = roomTileCreate(roomW + wallD, wallD + roomH / 2 - doorW / 2, wallD, doorW, RoomTile_Door);
				tile->doorDirection = 6;
			}
		}
		tile->linkRoom = linkRoom;
		room->tiles[room->tileCount++] = tile;
	}
}

void roomDispose(Room *room) {
	free(room);
}

void roomDraw(Room *room) {
	int x = room->px;
	int y = room->py;
	int fcolor = 0xff696969;
	int wcolor = 0xffa9a9a9;
	int dcolor = 0xff795548;
	for (int i = 0; i < room->tileCount; i++) {
		RoomTile *tile = room->tiles[i];
		switch (tile->type) {
		case RoomTile_Floor:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, fcolor);
			drawTextC(tile->caption, x + tile->x, y + tile->y, tile->w, tile->h, 90, 90, 90, 120);
			break;
		case RoomTile_Wall:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, wcolor);
			break;
		case RoomTile_Door:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, dcolor);
			break;
		default:
			break;
		}
	}
}
