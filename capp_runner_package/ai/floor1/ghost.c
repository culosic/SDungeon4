#include "ghost.h"

#include <base.h>
#include <ex_math.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../../room.h"
#include "../ai.h"

//////////////// 鬼 /////////////////

static void aiGhostInit(AIGhost *ai) {
	Role *role = ai->role;
	ai->state = AIGhost_Move;
	ai->attackAIT = 2;
	ai->attackCount = 10;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIGhost *aiGhostCreate(Role *role) {
	AIGhost *ai = create(sizeof(AIGhost));
	BollData *boll = role->boll->data;
	ai->role = role;
	ai->childCDT = 8;
	ai->childT = 1;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff000000;
	boll->r = 10;
	boll->v = 400;
	boll->atkv = 0.2;
	aiGhostInit(ai);
	return ai;
}

void aiGhostDispose(AIGhost *ai) {
	dispose(ai);
}

void aiGhostUpdate(AIGhost *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIGhost_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIGhost_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AIGhost_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, 0));
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiGhostInit(ai);
		}
		break;
	case AIGhost_State2:
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->turnAIT > 0) {
		ai->turnAIT -= t;
	} else {
		ai->turnAIT = getRandFloat(1, 1.5);
		roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
		}
	}
	if (ai->state != AIGhost_State2) {
		// 第一阶段，自动发射小鬼
		if (ai->childT > 0) {
			ai->childT -= t;
		} else {
			ai->childT = ai->childCDT;
			roomAddRole(room, roleCreate(RoleType_Ghost_Child, role->enemy, true), role->x, role->y);
			roomAddRole(room, roleCreate(RoleType_Ghost_Child, role->enemy, true), role->x, role->y);
		}
		// 切换到第二阶段
		if (role->hp < role->hps / 2) {
			ai->state = AIGhost_State2;
			Role *mainRole = roleCreate(RoleType_Ghost_Main, role->enemy, true);
			mainRole->hp = fmin(mainRole->hps, role->hp + 20);
			role->hp = 0;
			roomAddRole(room, mainRole, role->x, role->y);
			for (int i = 0; i < 3; i++) {
				roomAddRole(room, roleCreate(RoleType_Ghost_Child, role->enemy, true), role->x, role->y);
			}
		}
	}
}

//////////////// 鬼首领 /////////////////

static void aiGhostMainInit(AIGhostMain *ai) {
	Role *role = ai->role;
	role->v = role->data->v0;
	ai->state = AIGhostMain_Move;
	ai->attackT = 0.5;
	ai->attackAIT = 0.3;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIGhostMain *aiGhostMainCreate(Role *role) {
	AIGhostMain *ai = create(sizeof(AIGhostMain));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff000000;
	boll->r = 10;
	boll->v = 400;
	aiGhostMainInit(ai);
	return ai;
}

void aiGhostMainDispose(AIGhostMain *ai) {
	dispose(ai);
}

void aiGhostMainUpdate(AIGhostMain *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：移动=》连续冲刺=》移动
	switch (ai->state) {
	case AIGhostMain_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIGhostMain_Attack;
			ai->attackAIT = 0;
			role->v = data->v0 * 3;
			roleMove(role, aiGetAngleToEnemy(role, 0));
		}
		break;
	case AIGhostMain_Attack:
		ai->attackT -= t;
		Role *enemy = roomGetCloestEnemy(role->room, role);
		if (enemy && getLineSize(role->x, role->y, enemy->x, enemy->y) < data->r + enemy->data->r) {
			roleReduceHP(enemy, data->atk);
			role->faceAngle += M_PI;  // TODO 冲刺攻击后面需要来一段缓冲
			aiGhostMainInit(ai);
			ai->attackAIT = 0.6;  // 击中目标后，cd加长
		} else if (ai->attackT < 0) {
			// 体力耗尽，停止攻击。
			aiGhostMainInit(ai);
		}
		break;
	default:
		break;
	}
	if (ai->state == AIGhostMain_Move) {
		// 过一段时间就转向
		if (ai->turnAIT > 0) {
			ai->turnAIT -= t;
		} else {
			ai->turnAIT = getRandFloat(1, 1.5);
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
		}
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
		}
	}
	// 死亡，同时清理附属小鬼。
	if (role->hp <= 0) {
		for (int i = 0; i < room->roleCount; i++) {
			Role *r = room->roles[i];
			if (r->type == RoleType_Ghost_Child) {
				roleReduceHP(r, r->hps);
			}
		}
	}
}

//////////////// 小鬼 /////////////////

static void aiGhostChildInit(AIGhostChild *ai) {
	Role *role = ai->role;
	ai->state = AIGhostChild_Move;
	ai->attackAIT = getRandFloat(1, 2);
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIGhostChild *aiGhostChildCreate(Role *role) {
	AIGhostChild *ai = create(sizeof(AIGhostChild));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff000000;
	boll->r = 10;
	boll->v = 400;
	aiGhostChildInit(ai);
	return ai;
}

void aiGhostChildDispose(AIGhostChild *ai) {
	dispose(ai);
}

void aiGhostChildUpdate(AIGhostChild *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIGhostChild_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIGhostChild_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AIGhostChild_Attack:
		// 小鬼暂时设计为不能攻击，避免太乱。小鬼目的是阻挡主角行为和弹道。
		// TODO 撞击
		// if (role->attackingT == 0) {
		// 	roleAttack(role, aiGetAngleToEnemy(role, 0));
		// } else {
		// 	roleStopAttack(role);
		// }
		// 攻击结束，继续移动。
		aiGhostChildInit(ai);
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->turnAIT > 0) {
		ai->turnAIT -= t;
	} else {
		ai->turnAIT = getRandFloat(1, 1.5);
		roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 4));
		}
	}
}
