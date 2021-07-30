#include "bee.h"

#include <base.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiBeeInit(AIBee *ai) {
	Role *role = ai->role;
	ai->state = AIBee_Move;
	ai->attackAIT = 1;
	ai->attackCount = 6;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIBee *aiBeeCreate(Role *role) {
	AIBee *ai = create(sizeof(AIBee));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xffffaa1f;
	boll->r = 12;
	boll->v = 500;
	boll->atkv = 0.2;
	aiBeeInit(ai);
	ai->attackAIT = getRandFloat(0.3, ai->attackAIT);
	return ai;
}

void aiBeeDispose(AIBee *ai) {
	dispose(ai);
}

void aiBeeUpdate(AIBee *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIBee_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIBee_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AIBee_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, 0));
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiBeeInit(ai);
		}
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->turnAIT > 0) {
		ai->turnAIT -= t;
	} else {
		ai->turnAIT = getRandFloat(1, 1.5);
		roleMove(role, aiGetAngleToEnemy(role, M_PI / 8));
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 8));
		}
	}
}
