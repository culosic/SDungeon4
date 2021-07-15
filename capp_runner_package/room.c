#include "room.h"

#include <base.h>
#include <graphics.h>

#include "data.h"
#include "global.h"
#include "map.h"

RoomTile *roomTileCreate(int x, int y, int w, int h, enum RoomTileType type) {
	RoomTile *tile = create(sizeof(RoomTile));
	tile->x = x;
	tile->y = y;
	tile->w = w;
	tile->h = h;
	tile->type = type;
	return tile;
}

Room *roomCreate(Map *map, int x, int y, enum RoomType type) {
	Room *room = create(sizeof(Room));
	room->map = map;
	room->x = x;
	room->y = y;
	room->w = 10;
	room->h = 10;
	room->type = type;
	switch (type) {
	case Room_Init:
		room->caption = room_init_caption;
		break;
	case Room_Battle:
		room->caption = room_battle_caption;
		break;
	case Room_Potions:
		room->caption = room_potions_caption;
		break;
	case Room_Treasure:
		room->caption = room_treasure_caption;
		break;
	case Room_Boss:
		room->caption = room_boss_caption;
		break;
	default:
		room->caption = "";
		break;
	}
	room->roomW = 1000;
	room->roomH = 700;
	room->wallD = 30;
	room->doorW = 100;
	room->px = (SCRW - room->roomW) / 2 - room->wallD;
	room->py = (SCRH - room->roomH) / 2 - room->wallD;
	return room;
}

void roomInitTile(Room *room) {
	// 地板
	RoomTile *floor = roomTileCreate(room->wallD, room->wallD, room->roomW, room->roomH, RoomTile_Floor);
	floor->caption = room->caption;
	room->tiles[room->tileCount++] = floor;
	// 墙壁
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, room->roomW + room->wallD * 2, room->wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(room->roomW + room->wallD, 0, room->wallD, room->roomH + room->wallD * 2, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(0, room->roomH + room->wallD, room->roomW + room->wallD * 2, room->wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, room->wallD, room->roomH + room->wallD * 2, RoomTile_Wall);
	// 门
	for (int i = 0; i < room->linkRoomCount; i++) {
		Room *linkRoom = room->linkRooms[i];
		RoomTile *tile = NULL;
		if (room->x == linkRoom->x) {
			if (room->y > linkRoom->y) {  // 上
				tile = roomTileCreate(room->wallD + room->roomW / 2 - room->doorW / 2, 0, room->doorW, room->wallD, RoomTile_Door);
				tile->doorDirection = 2;
			} else {  // 下
				tile = roomTileCreate(room->wallD + room->roomW / 2 - room->doorW / 2, room->roomH + room->wallD, room->doorW, room->wallD, RoomTile_Door);
				tile->doorDirection = 8;
			}
		} else if (room->y == linkRoom->y) {
			if (room->x > linkRoom->x) {  // 左
				tile = roomTileCreate(0, room->wallD + room->roomH / 2 - room->doorW / 2, room->wallD, room->doorW, RoomTile_Door);
				tile->doorDirection = 4;
			} else {  // 右
				tile = roomTileCreate(room->roomW + room->wallD, room->wallD + room->roomH / 2 - room->doorW / 2, room->wallD, room->doorW, RoomTile_Door);
				tile->doorDirection = 6;
			}
		}
		tile->linkRoom = linkRoom;
		room->tiles[room->tileCount++] = tile;
	}
}

void roomDispose(Room *room) {
	for (int i = 0; i < room->roleCount; i++) {
		roleDispose(room->roles[i]);
	}
	for (int i = 0; i < room->tileCount; i++) {
		dispose(room->tiles[i]);
	}
	dispose(room);
}

void roomDraw(Room *room, double t) {
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
	for (int i = 0; i < room->roleCount; i++) {
		roleDraw(room->roles[i], t);
	}
}

void roomUpdate(Room *room, double t) {
	for (int i = 0; i < room->roleCount; i++) {
		roleUpdate(room->roles[i], t);
		roleUpdateAddition(room->roles[i], t);
	}
}

void roomAddRole(Room *room, struct _Role *role, float x, float y) {
	room->roles[room->roleCount++] = role;
	role->room = room;
	role->x = x;
	role->y = y;
}

void roomRoleGoto(Room *room, struct _Role *role, Room *newRoom) {
	int removed = false;
	for (int i = 0; i < room->roleCount; i++) {
		if (room->roles[i] == role) {
			removed = true;
			room->roleCount--;
			if (i == room->roleCount) {
				break;
			}
		}
		if (removed) {
			room->roles[i] = room->roles[i + 1];
		}
	}
	roomAddRole(newRoom, role, role->x, role->y);
}

RoomTile *roomColl(Room *room, float x, float y, float r) {
	RoomTile *collTile = NULL;
	for (int i = room->tileCount - 1; i >= 0; i--) {
		RoomTile *tile = room->tiles[i];
		if (tile->type != RoomTile_Floor) {
			if (isCirCollRect(x, y, r, tile->x, tile->y, tile->w, tile->h)) {
				if (tile->type == RoomTile_Door) {
					collTile = tile;
					break;
				} else if (tile->type == RoomTile_Wall) {
					collTile = tile;
					break;
				}
			}
		}
	}
	return collTile;
}

Role *roomCollEnemy(Room *room, float x, float y, float r, Role *role) {
	Role *result = NULL;
	for (int i = 0; i < room->roleCount; i++) {
		Role *enemy = room->roles[i];
		if (enemy->hp <= 0) {
			continue;
		}
		if (enemy->enemy != role->enemy && getLineSize(enemy->x, enemy->y, x, y) < enemy->data->r + r) {
			result = enemy;
		}
	}
	return result;
}

Role *roomGetCloestEnemy(Room *room, Role *role) {
	Role *result = NULL;
	float dist = -1;
	for (int i = 0; i < room->roleCount; i++) {
		Role *enemy = room->roles[i];
		if (enemy->hp <= 0) {
			continue;
		}
		if (enemy->enemy != role->enemy) {
			float d = getLineSize(enemy->x, enemy->y, role->x, role->y);
			if (dist < 0 || d < dist) {
				dist = d;
				result = enemy;
			}
		}
	}
	return result;
}
