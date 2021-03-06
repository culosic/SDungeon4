#include "role.h"

#include <base.h>
#include <ex_math.h>
#include <graphics.h>
#include <math.h>

#include "ai/floor1/ghost.h"
#include "ai/floor1/mouse.h"
#include "ai/floor1/scorpion.h"
#include "ai/floor1/wolf.h"
#include "ai/floor2/ant.h"
#include "ai/floor2/flamem.h"
#include "ai/floor2/frog.h"
#include "ai/floor2/snake.h"
#include "ai/floor3/bee.h"
#include "ai/floor3/edragon.h"
#include "ai/floor3/tiger.h"
#include "ai/floor3/tortoise.h"
#include "ai/player/longxin.h"
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
	case RoleType_Ghost_Main:
		data = &role_ghost_main;
		break;
	case RoleType_Ghost_Child:
		data = &role_ghost_child;
		break;

	case RoleType_Ant:
		data = &role_ant;
		break;
	case RoleType_Frog:
		data = &role_frog;
		break;
	case RoleType_Snake:
		data = &role_snake;
		break;

	case RoleType_FlameM:
		data = &role_flamem;
		break;

	case RoleType_Bee:
		data = &role_bee;
		break;
	case RoleType_Tiger:
		data = &role_tiger;
		break;
	case RoleType_Tortoise:
		data = &role_tortoise;
		break;

	case RoleType_EDragon:
		data = &role_edragon;
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
	case RoleType_LongXin:
		ai = aiLongxinCreate(role);
		break;

	case RoleType_Mouse:
		ai = aiMouseCreate(role);
		break;
	case RoleType_Wolf:
		ai = aiWolfCreate(role);
		break;
	case RoleType_Scorpion:
		ai = aiScorpionCreate(role);
		break;

	case RoleType_Ghost:
		ai = aiGhostCreate(role);
		break;
	case RoleType_Ghost_Main:
		ai = aiGhostMainCreate(role);
		break;
	case RoleType_Ghost_Child:
		ai = aiGhostChildCreate(role);
		break;

	case RoleType_Ant:
		ai = aiAntCreate(role);
		break;
	case RoleType_Frog:
		ai = aiFrogCreate(role);
		break;
	case RoleType_Snake:
		ai = aiSnakeCreate(role);
		break;

	case RoleType_FlameM:
		ai = aiFlameMCreate(role);
		break;

	case RoleType_Bee:
		ai = aiBeeCreate(role);
		break;
	case RoleType_Tiger:
		ai = aiTigerCreate(role);
		break;
	case RoleType_Tortoise:
		ai = aiTortoiseCreate(role);
		break;

	case RoleType_EDragon:
		ai = aiEdragonCreate(role);
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
	case RoleType_LongXin:
		aiLongxinDispose(ai);
		break;
	case RoleType_Mouse:
		aiMouseDispose(ai);
		break;
	case RoleType_Wolf:
		aiWolfDispose(ai);
		break;
	case RoleType_Scorpion:
		aiScorpionDispose(ai);
		break;

	case RoleType_Ghost:
		aiGhostDispose(ai);
		break;
	case RoleType_Ghost_Main:
		aiGhostMainDispose(ai);
		break;
	case RoleType_Ghost_Child:
		aiGhostChildDispose(ai);
		break;

	case RoleType_Ant:
		aiAntDispose(ai);
		break;
	case RoleType_Frog:
		aiFrogDispose(ai);
		break;
	case RoleType_Snake:
		aiSnakeDispose(ai);
		break;

	case RoleType_FlameM:
		aiFlameMDispose(ai);
		break;

	case RoleType_Bee:
		aiBeeDispose(ai);
		break;
	case RoleType_Tiger:
		aiTigerDispose(ai);
		break;
	case RoleType_Tortoise:
		aiTortoiseDispose(ai);
		break;

	case RoleType_EDragon:
		aiEdragonDispose(ai);
		break;

	default:
		break;
	}
}

static void roleUpdateAI(Role *role, double t) {
	void *ai = role->ai;
	if (!ai) {
		return;
	}
	switch (role->type) {
	case RoleType_LongXin:
		aiLongxinUpdate(ai, t);
		break;
	case RoleType_Mouse:
		aiMouseUpdate(ai, t);
		break;
	case RoleType_Wolf:
		aiWolfUpdate(ai, t);
		break;
	case RoleType_Scorpion:
		aiScorpionUpdate(ai, t);
		break;

	case RoleType_Ghost:
		aiGhostUpdate(ai, t);
		break;
	case RoleType_Ghost_Main:
		aiGhostMainUpdate(ai, t);
		break;
	case RoleType_Ghost_Child:
		aiGhostChildUpdate(ai, t);
		break;

	case RoleType_Ant:
		aiAntUpdate(ai, t);
		break;
	case RoleType_Frog:
		aiFrogUpdate(ai, t);
		break;
	case RoleType_Snake:
		aiSnakeUpdate(ai, t);
		break;

	case RoleType_FlameM:
		aiFlameMUpdate(ai, t);
		break;

	case RoleType_Bee:
		aiBeeUpdate(ai, t);
		break;
	case RoleType_Tiger:
		aiTigerUpdate(ai, t);
		break;
	case RoleType_Tortoise:
		aiTortoiseUpdate(ai, t);
		break;

	case RoleType_EDragon:
		aiEdragonUpdate(ai, t);
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
	role->atk = data->atk;
	role->v = role->v0 = data->v0;
	role->enemy = enemy;
	role->alive = true;

	role->boll = bollsCreate(5, 0xffffffff, 500, 0.3);
	role->hpPercentT = 1;
	role->dyingAlphaT = 1;

	if (ai) {
		role->ai = roleCreateAI(role);
	}
	role->atkv = role->boll->data->atkv;
	return role;
}

void roleDispose(Role *role) {
	bollsDispose(role->boll);
	roleDisposeAI(role);
	dispose(role);
}

void roleUpdate(Role *role, double t) {
	if (!role->alive) {
		return;
	}
	if (role->hp <= 0) {
		role->alive = false;
	}
	// AI
	roleUpdateAI(role, t);
	if (!role->alive) {
		return;
	}
	// ??????
	float sx = role->vx * t;
	float sy = role->vy * t;
	role->x += sx;
	role->y += sy;
	// ???????????????+?????????
	if (role->attacking && role->attackingT == 0) {
		bollAdd(role->boll, role, role->x, role->y, role->faceAngle);
	}
	if (role->attacking || role->attackingT > 0) {
		if (role->attackingT < role->atkv) {
			role->attackingT += t;
		} else {
			role->attackingT = 0;
		}
	}
}

void roleUpdateAddition(Role *role, double t) {
	// ????????????
	bollUpdate(role->boll, t);
}

void roleDraw(Role *role, double t) {
	RoleData *data = role->data;
	Room *room = role->room;
	int alive = role->hp > 0;
	float x = room->px + role->x;
	float y = room->py + role->y;
	// ????????????
	bollDraw(role->boll, t);
	// ????????????
	if (alive) {
		int fontSize = role->fw;
		drawCir(x, y, data->r + 3, data->color);
		drawCir(x, y, data->r, data->innerColor);
		drawText(data->caption, x - fontSize / 2, y - fontSize / 2 - fontSize / 8, 0xffE1E1F5, fontSize);
	} else {
		if (role->dyingAlphaT > 0) {  // ????????????
			role->dyingAlphaT = fmax(role->dyingAlphaT - 1.25 * t, 0);
			drawCir(x, y, data->r + 3, getAlphaColor(data->color, role->dyingAlphaT));
			drawCir(x, y, data->r, getAlphaColor(data->innerColor, role->dyingAlphaT));
		}
	}
	if (alive && !game.passed) {
		// ????????????
		int hpWidth = data->r * 2;
		int hpHeight = 6;
		int hpX = x - hpWidth / 2;
		int hpY = y - data->r - 10 - hpHeight;
		float hpPercent = role->hp / role->hps;
		if (role->hpPercentT > hpPercent) {	 // ????????????????????????
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
	role->moving = true;
	// if (!role->attacking) {	 // ?????????????????????????????????????????????????????????
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

void roleReduceHP(Role *role, float hpDT) {
	if (game.passed) {
		return;
	}
	role->hp = fmax(0, role->hp - hpDT);
}
