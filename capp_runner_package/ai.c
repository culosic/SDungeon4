#include "ai.h"

#include <math.h>

#include "base.h"
#include "data.h"
#include "global.h"
#include "role.h"

static void aiMouseInit(AIMouse *ai) {
	Role *role = ai->role;
	ai->state = AIMouse_Slow;
	ai->direction = getRandAngle();	 // TODO 改为慢速移动时转向
	ai->rushAIT = getRandFloat(0.5, 1.5);
	ai->rushCDT = 1;
	ai->rushT = 0;
	ai->attackCount = 0;
	roleStopAttack(role);
	roleMove(role, ai->direction);
}

AIMouse *aiMouseCreate(Role *role) {
	AIMouse *ai = create(sizeof(AIMouse));
	ai->role = role;
	aiMouseInit(ai);
	return ai;
}

void aiMouseDispose(AIMouse *ai) {
	dispose(ai);
}

void aiMouseUpdate(AIMouse *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 计算cd
	if (ai->rushCDT > 0) {
		ai->rushCDT = fmax(0, ai->rushCDT - t);
	}
	if (ai->tureCDT > 0) {
		ai->tureCDT = fmax(0, ai->tureCDT - t);
	}
	// 更新状态机：慢速移动=>高速移动=>攻击=>慢速移动...
	switch (ai->state) {
	case AIMouse_Slow:
		if (ai->rushAIT > 0) {
			ai->rushAIT = fmax(0, ai->rushAIT - t);
		} else if (ai->rushCDT == 0) {
			// 倒计时结束、cd转好，切换到高速状态
			ai->state = AIMouse_Rush;
			role->v = data->v0 * 2;
			Role *enemy = roomGetCloestEnemy(role->room, role);
			if (enemy) {
				ai->direction = getAngle(role->x, role->y, enemy->x, enemy->y);
			}
			roleMove(role, ai->direction);
		}
		break;
	case AIMouse_Rush:
		if (ai->rushT < 0.5) {
			ai->rushT += t;
		} else {
			// 高速移动完毕，切换到攻击状态
			ai->state = AIMouse_Attack;
			role->v = data->v0;
			roleMove(role, ai->direction);
		}
		break;
	case AIMouse_Attack:
		if (ai->attackCount < 3) {
			if (role->attackingT == 0) {
				Role *enemy = roomGetCloestEnemy(role->room, role);
				float attackDirection = enemy ? getAngle(role->x, role->y, enemy->x, enemy->y) : ai->direction;
				roleAttack(role, attackDirection);	// TODO 攻击主角方向
				ai->attackCount++;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，回到低速状态
			aiMouseInit(ai);
		}
		break;
	default:
		break;
	}
	// 碰撞减速、转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			ai->direction = getRandAngle();
			role->v = data->v0;
			roleMove(role, ai->direction);
		}
	}
}
