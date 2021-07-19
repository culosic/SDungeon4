#include "scorpion.h"

#include <base.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiScorpionInit(AIScorpion *ai) {
	Role *role = ai->role;
	ai->state = AIScorpion_Move;
	ai->attackAIT = getRandFloat(1, 2);
	ai->attackCount = 3;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIScorpion *aiScorpionCreate(Role *role) {
	AIScorpion *ai = create(sizeof(AIScorpion));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff6633aa;
	boll->r = 10;
	boll->v = 100;
	aiScorpionInit(ai);
	return ai;
}

void aiScorpionDispose(AIScorpion *ai) {
	dispose(ai);
}

void aiScorpionUpdate(AIScorpion *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIScorpion_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIScorpion_Attack;
			ai->attackAIT = 0;
			roleStopMove(role);
		}
		break;
	case AIScorpion_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, M_PI / 12));
				bollAdd(role->boll, role, role->x, role->y, aiGetAngleToEnemy(role, M_PI / 12));
				bollAdd(role->boll, role, role->x, role->y, aiGetAngleToEnemy(role, M_PI / 12));
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiScorpionInit(ai);
		}
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->state != AIScorpion_Attack) {
		if (ai->turnAIT > 0) {
			ai->turnAIT -= t;
		} else {
			ai->turnAIT = getRandFloat(2, 3);
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
}
