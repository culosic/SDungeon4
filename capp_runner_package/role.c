#include "role.h"

#include "base.h"
#include "boll.h"
#include "ex_math.h"
#include "global.h"
#include "map.h"
#include "room.h"

Role *roleCreate(Room *room, int x, int y) {
	Role *role = malloc(sizeof(Role));
	memset(role, 0, sizeof(Role));
	role->room = room;
	role->x = x;
	role->y = y;
	role->v0 = 300;
	role->boll = bollCreates(room, 5, 0xffffffff, 500, 300);
	return role;
}

void roleDispose(Role *role) {
	bollDispose(role->boll);
	free(role);
}

/**
 * @brief 跳转房间
 */
static void roleGotoRoom(Role *role, Room *room) {
	Room *originRoom = role->room;
	Map *map = originRoom->map;
	role->room = map->currentRoom = room;
}

void roleUpdate(Role *role, float t) {
	float oldx = role->x;
	float oldy = role->y;
	// 移动
	role->x += role->vx * t;
	role->y += role->vy * t;
	// 攻击
	if (role->attacking || role->attackingT > 0) {
		if (role->attackingT < 0.3) {  // TODO 攻速应该是role里的
			role->attackingT += t;
		} else {
			role->attackingT = 0;
			bollAdd(role->boll, role->x, role->y, role->faceAngle);
		}
	}
	// 碰撞检测
	if (role->vx > 0 || role->vy > 0) {
		int r = 22;
		Room *room = role->room;
		for (int i = room->tileCount - 1; i >= 0; i--) {
			RoomTile *tile = room->tiles[i];
			if (tile->type != RoomTile_Floor) {
					printf("%.3f, %.3f----%d\n", role->x, role->y, isCirCollRect(role->x, role->y, r, tile->x, tile->y, tile->w, tile->h));
				if (isCirCollRect(role->x, role->y, r, tile->x, tile->y, tile->w, tile->h)) {
					if (tile->type == RoomTile_Door) {
						// 切换房间
						float roomW = 500;	// 房间x宽度
						float roomH = 500;	// 房间y宽度
						float wallD = 30;	// 墙壁厚度
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
						role->x = oldx;
						role->y = oldy;
						// TODO 碰撞墙壁后贴住墙壁。
						// 墙壁碰撞
						// switch (role->direction) {
						// case 2:
						// 	role->y = tile->y + r + tile->h + 1;
						// 	break;
						// case 6:
						// 	role->x = tile->x - r - 1;
						// 	break;
						// case 8:
						// 	role->y = tile->y - r - 1;
						// 	break;
						// case 4:
						// 	role->x = tile->x + r + tile->w + 1;
						// 	break;
						// default:
						// 	break;
						// }
					}
					break;
				}
			}
		}
	}
	// 子弹检测
	bollUpdate(role->boll, t);
}

void roleDraw(Role *role) {
	int r = 20;
	int rb = 2;
	Room *room = role->room;
	float x = room->px + role->x;
	float y = room->py + role->y;
	// 绘制子弹
	bollDraw(role->boll);
	// 绘制人物
	drawCir(x, y, r + rb * 2, 0xff009688);
	drawCir(x, y, r, 0x77005737);
	drawTextC(utf8_c("我"), x - r, y - r, r * 2, r * 2, 225, 225, 245, 20);
}

void roleMove(Role *role, double angle) {
	role->moving = true;
	// if (!role->attacking) {	 // 仅移动时，攻击方向跟攻击方向保持一直。
	role->faceAngle = angle;
	// }
	role->vx = role->v0 * cos(angle);
	role->vy = role->v0 * sin(angle);
}

void roleStopMove(Role *role) {
	role->vy = role->vx = 0;
	role->moving = false;
}

void roleAttack(Role *role, double angle) {
	role->attacking = true;
	role->faceAngle = angle;
}

void roleStopAttack(Role *role) {
	role->attacking = false;
}
