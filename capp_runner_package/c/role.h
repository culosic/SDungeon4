#ifndef _ROLE_H_
#define _ROLE_H_

#ifdef CAPP
#include "base.h"
#include "ex_math.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "global.h"
#include "map.h"
#include "room.h"

// 角色数据定义
typedef struct _Role {
	Room *room;
	float x;
	float y;
	float v0;
	int direction;	// 移动方向
	float v;		// 当前速度
} Role;

/**
 * 初始化
 */
Role *roleInit(Room *room, int x, int y) {
	Role *role = malloc(sizeof(Role));
	memset(role, 0, sizeof(Role));
	role->room = room;
	role->x = x;
	role->y = y;
	role->v0 = 600;
	return role;
}

/**
 * 释放角色占用内存
 */
void roleDispose(Role *role) {
	free(role);
}

void roleGotoRoom(Role *role, Room *room) {
	Room *originRoom = role->room;
	Map *map = originRoom->map;
	role->room = map->currentRoom = room;
}

/**
 * 更新角色
 */
void roleUpdate(Role *role, float t) {
	if (role->direction) {
		role->v = role->v0;
	} else {
		role->v = 0;
	}
	switch (role->direction) {
	case 2:
		role->y -= role->v * t;
		break;
	case 6:
		role->x += role->v * t;
		break;
	case 8:
		role->y += role->v * t;
		break;
	case 4:
		role->x -= role->v * t;
		break;
	default:
		break;
	}
	// 碰撞检测
	if (role->direction) {
		int r = 22;
		Room *room = role->room;
		for (int i = room->tileCount - 1; i >= 0; i--) {
			RoomTile *tile = room->tiles[i];
			if (tile->type != RoomTile_Floor) {
				if (isCirCollRect(role->x, role->y, r, tile->x, tile->y, tile->w, tile->h)) {
					if (tile->type == RoomTile_Door) {
						// 切换房间
						float roomW = 500;	// 房间x宽度
						float roomH = 500;	// 房间y宽度
						float wallD = 30;	// 墙壁厚度
						float doorW = 80;	// 门宽度
						float x = role->x;
						float y = role->y;
						switch (tile->doorDirection) {
						case 2:
							role->y = roomH + wallD - r;
							break;
						case 6:
							role->x = wallD + r;
							break;
						case 8:
							role->y = wallD + r;
							break;
						case 4:
							role->x = roomW + wallD - r;
							break;
						default:
							break;
						}
						roleGotoRoom(role, tile->linkRoom);
					} else if (tile->type == RoomTile_Wall) {
						// 墙壁碰撞
						switch (role->direction) {
						case 2:
							role->y = tile->y + r + tile->h + 1;
							break;
						case 6:
							role->x = tile->x - r - 1;
							break;
						case 8:
							role->y = tile->y - r - 1;
							break;
						case 4:
							role->x = tile->x + r + tile->w + 1;
							break;
						default:
							break;
						}
					}
					break;
				}
			}
		}
	}
}

/**
 * 角色控制事件
 */
void roleEvent(Role *role, int type, int p, int q) {
	int keyDirection = 0;
	switch (p) {
	case _UP:
		keyDirection = 2;
		break;
	case _RIGHT:
		keyDirection = 6;
		break;
	case _DOWN:
		keyDirection = 8;
		break;
	case _LEFT:
		keyDirection = 4;
		break;
	default:
		break;
	}
	if (type == KY_DOWN) {
		if (keyDirection) {
			role->direction = keyDirection;
		}
	} else if (type == KY_UP) {
		if (keyDirection && keyDirection == role->direction) {	// 兼容两个方向键同时按下的情况
			role->direction = 0;
		}
	}
}

#endif