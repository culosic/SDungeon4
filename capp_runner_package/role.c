#include "role.h"

#include <base.h>
#include <ex_math.h>
#include <graphics.h>
#include <math.h>

#include "ai/floor1/mouse.h"
#include "ai/floor1/scorpion.h"
#include "ai/floor1/wolf.h"
#include "boll.h"
#include "data.h"
#include "game.h"
#include "global.h"
#include "map.h"
#include "room.h"

static RoleData *roleGetData(enum RoleType type) {
	RoleData *data = NULL;
	switch (type) {
	case RoleType_LongXin:
		data = &role_longxin;
		break;
	case RoleType_JingYu:
		data = &role_jingyu;
		break;
	case RoleType_Wu_JingYu:
		data = &role_wu_jingyu;
		break;
	case RoleType_Ne_Giles:
		data = &role_ne_giles;
		break;
	case RoleType_Clark:
		data = &role_clark;
		break;

	case RoleType_Mouse:
		data = &role_mouse;
		break;
	case RoleType_Wolf:
		data = &role_wolf;
		break;
	case RoleType_Scorpion:
		data = &role_scorpion;
		break;

	case RoleType_Ghost:
		data = &role_ghost;
		break;
	default:
		data = &role_mouse;
		break;
	}
	return data;
}

static void *roleCreateAI(Role *role) {
	void *ai = NULL;
	switch (role->type) {
	case RoleType_Mouse:
		ai = aiMouseCreate(role);
		break;
	case RoleType_Wolf:
		ai = aiWolfCreate(role);
		break;
	case RoleType_Scorpion:
		ai = aiScorpionCreate(role);
		break;
	default:
		break;
	}
	return ai;
}

static void roleDisposeAI(Role *role) {
	if (!role->ai) {
		return;
	}
	void *ai = role->ai;
	switch (role->type) {
	case RoleType_Mouse:
		aiMouseDispose(ai);
		break;
	case RoleType_Wolf:
		aiWolfDispose(ai);
		break;
	case RoleType_Scorpion:
		aiScorpionDispose(ai);
		break;
	default:
		break;
	}
}

static void roleUpdateAI(Role *role, double t) {
	if (!role->ai) {
		return;
	}
	void *ai = role->ai;
	switch (role->type) {
	case RoleType_Mouse:
		aiMouseUpdate(ai, t);
		break;
	case RoleType_Wolf:
		aiWolfUpdate(ai, t);
		break;
	case RoleType_Scorpion:
		aiScorpionUpdate(ai, t);
		break;
	default:
		break;
	}
}

Role *roleCreate(enum RoleType type, int enemy, int ai) {
	Role *role = create(sizeof(Role));
	RoleData *data = role->data = roleGetData(type);
	role->type = type;
	role->fw = data->r * 2 > 20 / 0.5 ? data->r * 2 > 70 / 0.5 ? 70 : data->r * 2 * 0.5 : 20;
	role->hp = data->hp;
	role->hps = data->hp;
	role->mp = data->mp;
	role->mps = data->mp;
	role->v = data->v0;
	role->enemy = enemy;

	role->boll = bollsCreate(5, 0xffffffff, 500, 300);
	role->hpPercentT = 1;
	role->dyingAlphaT = 1;

	if (ai) {
		role->ai = roleCreateAI(role);
	}
	return role;
}

void roleDispose(Role *role) {
	bollsDispose(role->boll);
	roleDisposeAI(role);
	dispose(role);
}

/**
 * @brief 跳转房间
 */
static void roleGotoRoom(Role *role, Room *room) {
	Room *originRoom = role->room;
	Map *map = originRoom->map;
	// TODO 应该由房间的门来让角色跳转房间。
	roomRoleGoto(originRoom, role, room);
	map->currentRoom = room;  // TODO 仅主角。
}

void roleUpdate(Role *role, double t) {
	if (role->hp <= 0) {
		return;
	}
	RoleData *data = role->data;
	// AI
	roleUpdateAI(role, t);
	// 移动
	float sx = role->vx * t;
	float sy = role->vy * t;
	role->x += sx;
	role->y += sy;
	// 攻击（发射+后摇）
	if (role->attacking && role->attackingT == 0) {
		bollAdd(role->boll, role, role->x, role->y, role->faceAngle);
	}
	if (role->attacking || role->attackingT > 0) {
		if (role->attackingT < 0.3) {  // TODO 使用武器的攻速
			role->attackingT += t;
		} else {
			role->attackingT = 0;
		}
	}
	// 碰撞检测
	int xStopped = false;
	int yStopped = false;
	if (role->vx != 0 && role->vy != 0) {
		Room *room = role->room;
		RoomTile *tile = roomColl(room, role->x, role->y, data->r);
		if (tile && tile->type) {
			switch (tile->type) {
			case RoomTile_Door:
				// 切换房间
				if (role != game.mainRole) {
					break;	// 非主角，不能切换房间。
				}
				switch (tile->doorDirection) {
				case 2:
					role->y = room->roomH + room->wallD - data->r - 10;
					break;
				case 6:
					role->x = room->wallD + data->r + 10;
					break;
				case 8:
					role->y = room->wallD + data->r + 10;
					break;
				case 4:
					role->x = room->roomW + room->wallD - data->r - 10;
					break;
				default:
					break;
				}
				roleGotoRoom(role, tile->linkRoom);
				break;
			case RoomTile_Wall:
				// 墙壁碰撞
				if (isCirCollRect(role->x, role->y - sy, data->r, tile->x, tile->y, tile->w, tile->h)) {
					xStopped = true;
				}
				if (isCirCollRect(role->x - sx, role->y, data->r, tile->x, tile->y, tile->w, tile->h)) {
					yStopped = true;
				}
				break;
			default:
				break;
			}
		}
	}
	if (xStopped) {
		role->x -= sx;
	}
	if (yStopped) {
		role->y -= sy;
	}
}

void roleUpdateAddition(Role *role, double t) {
	// 子弹检测
	bollUpdate(role->boll, t);
}

void roleDraw(Role *role, double t) {
	RoleData *data = role->data;
	Room *room = role->room;
	int alive = role->hp > 0;
	float x = room->px + role->x;
	float y = room->py + role->y;
	// 绘制子弹
	bollDraw(role->boll, t);
	// 绘制人物
	if (alive) {
		int fontSize = role->fw;
		drawCir(x, y, data->r + 3, data->color);
		drawCir(x, y, data->r, data->innerColor);
		drawText(data->caption, x - fontSize / 2, y - fontSize / 2 - fontSize / 8, 225, 225, 245, fontSize);
	} else {
		if (role->dyingAlphaT > 0) {  // 死亡渐隐
			role->dyingAlphaT = fmax(role->dyingAlphaT - 1.25 * t, 0);
			drawCir(x, y, data->r + 3, getAlphaColor(data->color, role->dyingAlphaT));
			drawCir(x, y, data->r, getAlphaColor(data->innerColor, role->dyingAlphaT));
		}
	}
	if (alive) {
		// 绘制血条
		int hpWidth = data->r * 2;
		int hpHeight = 6;
		int hpX = x - hpWidth / 2;
		int hpY = y - data->r - 10 - hpHeight;
		float hpPercent = role->hp / role->hps;
		if (role->hpPercentT > hpPercent) {	 // 血条的扣血动画。
			role->hpPercentT = fmax(role->hpPercentT - fmax(0.2, hp_decrease_animation_v * (role->hpPercentT - hpPercent)) * t, hpPercent);
		}
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
		drawRect(hpX, hpY, hpWidth, hpHeight, 0xff660000);
		drawRect(hpX, hpY, hpWidth * role->hpPercentT, hpHeight, 0xffff0000);
		drawRect(hpX, hpY, hpWidth * hpPercent, hpHeight, role->enemy ? 0xffbb0000 : 0xff4caf50);
	}
}

void roleMove(Role *role, double angle) {
	RoleData *data = role->data;
	role->moving = true;
	// if (!role->attacking) {	 // 仅移动时，攻击方向跟攻击方向保持一直。
	role->faceAngle = angle;
	// }
	role->vx = role->v * cos(angle);
	role->vy = role->v * sin(angle);
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
