#include "wolf.h"

#include <base.h>
#include <ex_math.h>
#include <math.h>

#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiWolfInit(AIWolf *ai) {
	Role *role = ai->role;
	role->v = role->data->v0;
	ai->state = AIWolf_Move;
	ai->chargeT = 0.3;
	ai->attackT = 0.6;
	ai->attackAIT = 0.3;
	ai->turnAIT = 0;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIWolf *aiWolfCreate(Role *role) {
	AIWolf *ai = create(sizeof(AIWolf));
	ai->role = role;
	aiWolfInit(ai);
	ai->attackAIT = getRandFloat(0.3, ai->attackAIT * 2);
	return ai;
}

void aiWolfDispose(AIWolf *ai) {
	dispose(ai);
}

void aiWolfUpdate(AIWolf *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：蓄力=>攻击=>移动片刻=>再次蓄力攻击...
	switch (ai->state) {
	case AIWolf_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 开始蓄力，减速后退
			Role *enemy = roomGetCloestEnemy(role->room, role);
			if (!enemy) {
				break;	// 没有敌人，继续移动。
			}
			// if (getLineSize(role->x, role->y, enemy->x, enemy->y) < 300) {	// 进入攻击范围
			ai->state = AIWolf_Charge;
			ai->attackDirection = getAngle(role->x, role->y, enemy->x, enemy->y);
			role->v = data->v0 * 0.6;
			roleMove(role, ai->attackDirection + M_PI);
			// }
		}
		break;
	case AIWolf_Charge:
		if (ai->chargeT > 0) {
			ai->chargeT -= t;
		} else {
			// 蓄力完毕，开始攻击。
			// TODO 应该是加速运动，不是匀速运动。
			ai->state = AIWolf_Attack;
			role->v = data->v0 * 5;
			roleMove(role, ai->attackDirection);
		}
		break;
	case AIWolf_Attack:
		// TODO 改成路径上造成伤害。记录本次路径上已造成伤害的角色。
		ai->attackT -= t;
		Role *enemy = roomGetCloestEnemy(role->room, role);
		if (enemy && getLineSize(role->x, role->y, enemy->x, enemy->y) < data->r + enemy->data->r) {
			roleReduceHP(enemy, data->atk);
			role->faceAngle += M_PI;  // TODO 冲刺攻击后面需要来一段缓冲
			aiWolfInit(ai);
		} else if (ai->attackT < 0) {
			// 体力耗尽，停止攻击。
			aiWolfInit(ai);
		}
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->state == AIWolf_Move) {
		if (ai->turnAIT > 0) {
			ai->turnAIT -= t;
		} else {
			ai->turnAIT = getRandFloat(1, 1.5);
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 12));
		}
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			if (ai->state != AIWolf_Charge) {
				role->v = data->v0;
				roleMove(role, aiGetAngleToEnemy(role, M_PI / 12));
				// 撞墙结束冲刺
				if (ai->state == AIWolf_Attack) {
					aiWolfInit(ai);
				}
			}
		}
	}
}
