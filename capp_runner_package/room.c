#include "room.h"

#include <base.h>
#include <graphics.h>

#include "data.h"
#include "game.h"
#include "global.h"
#include "map.h"

RoomTile *roomTileCreate(int x, int y, int w, int h, enum RoomTileType type, int direction) {
	RoomTile *tile = create(sizeof(RoomTile));
	tile->x = x;
	tile->y = y;
	tile->w = w;
	tile->h = h;
	tile->type = type;
	tile->direction = direction;
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
		room->roomW = 300;
		room->roomH = 300;
		break;
	case Room_Battle:
		room->caption = room_battle_caption;
		room->roomW = 700;
		room->roomH = 500;
		break;
	case Room_Potions:
		room->caption = room_potions_caption;
		room->roomW = 400;
		room->roomH = 400;
		break;
	case Room_Treasure:
		room->caption = room_treasure_caption;
		room->roomW = 400;
		room->roomH = 400;
		break;
	case Room_Boss:
		room->caption = room_boss_caption;
		room->roomW = 900;
		room->roomH = 700;
		break;
	default:
		room->caption = "";
		room->roomW = 100;
		room->roomH = 100;
		break;
	}
	room->wallD = 30;
	room->doorW = 100;
	room->roomW -= room->wallD * 2;
	room->roomH -= room->wallD * 2;
	room->px = (SCRW - room->roomW) / 2;
	room->py = (SCRH - room->roomH) / 2;
	return room;
}

void roomInitTile(Room *room) {
	// 地板
	RoomTile *floor = roomTileCreate(room->wallD, room->wallD, room->roomW, room->roomH, RoomTile_Floor, 0);
	floor->caption = room->caption;
	room->tiles[room->tileCount++] = floor;
	// 墙壁
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, room->roomW + room->wallD * 2, room->wallD, RoomTile_Wall, 2);
	room->tiles[room->tileCount++] = roomTileCreate(room->roomW + room->wallD, 0, room->wallD, room->roomH + room->wallD * 2, RoomTile_Wall, 6);
	room->tiles[room->tileCount++] = roomTileCreate(0, room->roomH + room->wallD, room->roomW + room->wallD * 2, room->wallD, RoomTile_Wall, 8);
	room->tiles[room->tileCount++] = roomTileCreate(0, 0, room->wallD, room->roomH + room->wallD * 2, RoomTile_Wall, 4);
	// 门
	for (int i = 0; i < room->linkRoomCount; i++) {
		Room *linkRoom = room->linkRooms[i];
		RoomTile *tile = NULL;
		if (room->x == linkRoom->x) {
			if (room->y > linkRoom->y) {  // 上
				tile = roomTileCreate(room->wallD + room->roomW / 2 - room->doorW / 2, 0, room->doorW, room->wallD, RoomTile_Door, 2);
			} else {  // 下
				tile = roomTileCreate(room->wallD + room->roomW / 2 - room->doorW / 2, room->roomH + room->wallD, room->doorW, room->wallD, RoomTile_Door, 8);
			}
		} else if (room->y == linkRoom->y) {
			if (room->x > linkRoom->x) {  // 左
				tile = roomTileCreate(0, room->wallD + room->roomH / 2 - room->doorW / 2, room->wallD, room->doorW, RoomTile_Door, 4);
			} else {  // 右
				tile = roomTileCreate(room->roomW + room->wallD, room->wallD + room->roomH / 2 - room->doorW / 2, room->wallD, room->doorW, RoomTile_Door, 6);
			}
		}
		tile->linkRoom = linkRoom;
		room->tiles[room->tileCount++] = tile;
	}
}

void roomDispose(Room *room) {
	for (int i = 0; i < room->roleCount; i++) {
		if (room->roles[i] == game.mainRole) {
			continue;  // TODO 暂时不销毁主角，交给game去销毁。
		}
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
	for (int i = 0; i < room->tileCount; i++) {
		RoomTile *tile = room->tiles[i];
		switch (tile->type) {
		case RoomTile_Floor:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, 0xff696969);
			drawTextC(tile->caption, x + tile->x, y + tile->y, tile->w, tile->h, 90, 90, 90, 120);
			break;
		case RoomTile_Wall:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, 0xffa9a9a9);
			break;
		case RoomTile_Door:
			if (tile->doorClosed) {
				drawRect(x + tile->x, y + tile->y, tile->w, tile->h, 0xffa9a9a9);
			} else {
				drawRect(x + tile->x, y + tile->y, tile->w, tile->h, 0xff795548);
			}
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < room->roleCount; i++) {
		roleDraw(room->roles[i], t);
	}
}

static void roomToggleDoor(Room *room, int direction) {
	for (int i = room->tileCount - 1; i >= 0; i--) {
		RoomTile *tile = room->tiles[i];
		if (tile->type == RoomTile_Door && (room->type == Room_Boss || tile->direction != direction)) {
			tile->doorClosed = true;
		}
	}
}

RoomTile *room_colls_tiles[10];
int room_colls_count = 0;

static void roomColls(Room *room, float x, float y, float r) {
	room_colls_count = 0;
	for (int i = room->tileCount - 1; i >= 0; i--) {
		RoomTile *tile = room->tiles[i];
		if (isCirCollRect(x, y, r, tile->x, tile->y, tile->w, tile->h)) {
			if (tile->type == RoomTile_Door && !tile->doorClosed) {
				room_colls_tiles[room_colls_count++] = tile;
				break;
			} else if (tile->type == RoomTile_Wall) {
				room_colls_tiles[room_colls_count++] = tile;
			}
		}
	}
}

/**
 * @brief 碰撞检测。
 * 
 * @param room 
 * @param role 
 */
static void roomUpdateColl(Room *room, Role *role) {
	Map *map = room->map;
	RoleData *data = role->data;
	if (role->vx != 0 && role->vy != 0) {
		roomColls(room, role->x, role->y, data->r);
		for (int i = 0; i < room_colls_count; i++) {
			RoomTile *tile = room_colls_tiles[i];
			Room *linkRoom = tile->linkRoom;
			switch (tile->type) {
			case RoomTile_Door:
				// 切换房间
				if (role == game.mainRole) {  // TODO 非主角，暂时不能切换房间。
					switch (tile->direction) {
					case 2:
						role->x = linkRoom->roomW / 2.0 + linkRoom->wallD;
						role->y = linkRoom->roomH + linkRoom->wallD - data->r - 10;
						break;
					case 6:
						role->x = linkRoom->wallD + data->r + 10;
						role->y = linkRoom->roomH / 2.0 + linkRoom->wallD;
						break;
					case 8:
						role->x = linkRoom->roomW / 2.0 + linkRoom->wallD;
						role->y = linkRoom->wallD + data->r + 10;
						break;
					case 4:
						role->x = linkRoom->roomW + linkRoom->wallD - data->r - 10;
						role->y = linkRoom->roomH / 2.0 + linkRoom->wallD;
						break;
					default:
						break;
					}
					if (!linkRoom->passed) {
						roomToggleDoor(linkRoom, 10 - tile->direction);
					}
					roomRoleGoto(room, role, linkRoom);
					map->currentRoom = linkRoom;
				}
				break;
			case RoomTile_Wall:
				// 碰撞墙壁
				switch (tile->direction) {
				case 2:
					if (role->vy < 0) {
						role->y = tile->y + tile->h + data->r + 1;
					}
					break;
				case 6:
					if (role->vx > 0) {
						role->x = tile->x - data->r - 1;
					}
					break;
				case 8:
					if (role->vy > 0) {
						role->y = tile->y - data->r - 1;
					}
					break;
				case 4:
					if (role->vx < 0) {
						role->x = tile->x + tile->w + data->r + 1;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

void roomUpdate(Room *room, double t) {
	int passed = true;
	for (int i = 0; i < room->roleCount; i++) {
		Role *role = room->roles[i];
		if (role->enemy && role->hp > 0) {
			passed = false;
		}
		roleUpdate(role, t);
		roomUpdateColl(room, role);
		roleUpdateAddition(role, t);
	}
	if (!room->passed && passed) {
		room->passed = true;
		for (int i = room->tileCount - 1; i >= 0; i--) {
			RoomTile *tile = room->tiles[i];
			if (tile->type == RoomTile_Door) {
				tile->doorClosed = false;
			}
		}
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
				if (tile->type == RoomTile_Door && !tile->doorClosed) {
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
