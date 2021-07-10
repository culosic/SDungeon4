#include "role.h"

#include "base.h"
#include "boll.h"
#include "ex_math.h"
#include "global.h"
#include "graphics.h"
#include "map.h"
#include "room.h"

Role *roleCreate(RoleData *data, struct _Room *room, int x, int y, int enemy) {
	Role *role = malloc(sizeof(Role));
	memset(role, 0, sizeof(Role));
	role->data = data;
	role->fw = data->r * 2 > 20 / 0.5 ? data->r * 2 > 70 / 0.5 ? 70 : data->r * 2 * 0.5 : 20;
	printf("r:%d,   fw:%d\n", data->r, role->fw);
	role->room = room;
	role->hp = data->hp;
	role->hps = data->hp;
	role->mp = data->mp;
	role->mps = data->mp;

	role->enemy = enemy;
	role->x = x;
	role->y = y;
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
	RoleData *data = role->data;
	float sx = role->vx * t;
	float sy = role->vy * t;
	// 移动
	role->x += sx;
	role->y += sy;
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
	int xcoll = false;
	int ycoll = false;
	if (role->vx != 0 && role->vy != 0) {
		int r = data->r;
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
						break;
					} else if (tile->type == RoomTile_Wall) {
						// 墙壁碰撞
						if (isCirCollRect(role->x, role->y - sy, r, tile->x, tile->y, tile->w, tile->h)) {
							xcoll = true;
						}
						if (isCirCollRect(role->x - sx, role->y, r, tile->x, tile->y, tile->w, tile->h)) {
							ycoll = true;
						}
					}
				}
			}
		}
	}
	if (xcoll) {
		role->x -= sx;
	}
	if (ycoll) {
		role->y -= sy;
	}
	// 子弹检测
	bollUpdate(role->boll, t);
}

void roleDraw(Role *role) {
	RoleData *data = role->data;
	int r = data->r;
	int b = 3;
	int fontSize = role->fw;
	Room *room = role->room;
	float x = room->px + role->x;
	float y = room->py + role->y;
	// 绘制子弹
	bollDraw(role->boll);
	// 绘制人物
	drawCir(x, y, r + b, data->color);
	drawCir(x, y, r, data->innerColor);
	drawText(data->caption, x - fontSize / 2, y - fontSize / 2 - fontSize / 8, 225, 225, 245, fontSize);
	// 绘制血条
	int hpWidth = r * 2;
	int hpHeight = 6;
	int hpX = x - hpWidth / 2;
	int hpY = y - r - 10 - hpHeight;
	float hpPercent = role->hp / role->hps - 0.5;  // TODO test
	if (hpX < 0) {
		hpX = 0;
	} else if (hpX > SCRW - hpWidth) {
		hpX = SCRW - hpWidth;
	}
	if (hpY < 0) {
		hpY = 0;
	} else if (hpY > SCRH - hpHeight) {
		hpY = SCRH - hpHeight;
	}
	drawRect(hpX, hpY, hpWidth, hpHeight, role->enemy ? 0xff600000 : 0xff222222);
	drawRect(hpX, hpY, hpWidth * hpPercent, hpHeight, role->enemy ? 0xffcc0000 : 0xff4caf50);
}

void roleMove(Role *role, double angle) {
	RoleData *data = role->data;
	role->moving = true;
	// if (!role->attacking) {	 // 仅移动时，攻击方向跟攻击方向保持一直。
	role->faceAngle = angle;
	// }
	role->vx = data->v0 * cos(angle);
	role->vy = data->v0 * sin(angle);
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
