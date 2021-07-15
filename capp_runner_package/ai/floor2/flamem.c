#include "flamem.h"

#include <base.h>
#include <ex_math.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../../room.h"
#include "../ai.h"

static void aiFlameMInit(AIFlameM *ai) {
	Role *role = ai->role;
	ai->state = AIFlameM_Move;
	ai->attackAIT = 1;
	ai->attackCount = 10;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIFlameM *aiFlameMCreate(Role *role) {
	AIFlameM *ai = create(sizeof(AIFlameM));
	BollData *boll = role->boll->data;
	ai->role = role;
	ai->childCDT = 8;
	ai->childT = 1;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xffff7700;
	boll->r = 10;
	boll->v = 400;
	aiFlameMInit(ai);
	return ai;
}

void aiFlameMDispose(AIFlameM *ai) {
	dispose(ai);
}

void aiFlameMUpdate(AIFlameM *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIFlameM_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIFlameM_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AIFlameM_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, M_PI / 6));
				for (int i = 0; i < 3; i++) {
					bollAdd(role->boll, role, role->x, role->y, aiGetAngleToEnemy(role, M_PI / 6));
				}
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiFlameMInit(ai);
		}
		break;
	case AIFlameM_State2:
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
