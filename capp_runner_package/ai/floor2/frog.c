#include "frog.h"

#include <base.h>
#include <ex_math.h>
#include <math.h>

#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiFrogInit(AIFrog *ai) {
	Role *role = ai->role;
	role->v = role->data->v0;
	ai->state = AIFrog_Idle;
	ai->attackT = 0.2;
	ai->attackAIT = 1;
	roleStopMove(role);
}

AIFrog *aiFrogCreate(Role *role) {
	AIFrog *ai = create(sizeof(AIFrog));
	ai->role = role;
	aiFrogInit(ai);
	return ai;
}

void aiFrogDispose(AIFrog *ai) {
	dispose(ai);
}

void aiFrogUpdate(AIFrog *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机
	switch (ai->state) {
	case AIFrog_Idle:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			Role *enemy = roomGetCloestEnemy(role->room, role);
			if (!enemy) {
				break;	// 没有敌人，继续移动。
			}
			ai->state = AIFrog_Attack;
			ai->attackDirection = getAngle(role->x, role->y, enemy->x, enemy->y);
			role->v = data->v0 * 10;
			roleMove(role, ai->attackDirection);
		}
		break;
	case AIFrog_Attack:
		ai->attackT -= t;
		Role *enemy = roomGetCloestEnemy(role->room, role);
		if (enemy && getLineSize(role->x, role->y, enemy->x, enemy->y) < data->r + enemy->data->r) {
			enemy->hp = fmax(0, enemy->hp - data->atk);
			aiFrogInit(ai);
		} else if (ai->attackT < 0) {
			// 体力耗尽，停止攻击。
			aiFrogInit(ai);
		}
		break;
	default:
		break;
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			// 撞墙结束冲刺
			if (ai->state == AIFrog_Attack) {
				aiFrogInit(ai);
			}
		}
	}
}
