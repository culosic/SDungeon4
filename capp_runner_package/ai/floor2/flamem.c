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
	ai->state = AIFlameM_Idle;
	ai->attackAIT = 2;
	ai->attackCount = 3;
	roleStopAttack(role);
}

AIFlameM *aiFlameMCreate(Role *role) {
	AIFlameM *ai = create(sizeof(AIFlameM));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xffff7700;
	boll->r = 10;
	boll->v = 400;
	boll->atkv = 0.5;
	aiFlameMInit(ai);
	ai->attackAIT = 0.3;
	return ai;
}

void aiFlameMDispose(AIFlameM *ai) {
	dispose(ai);
}

void aiFlameMUpdate(AIFlameM *ai, double t) {
	Role *role = ai->role;
	double pa = M_PI * 2 * 1 / 48;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIFlameM_Idle:
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
				roleAttack(role, aiGetAngleToEnemy(role, 0));
				bollAdd(role->boll, role, role->x, role->y, role->faceAngle + pa);
				bollAdd(role->boll, role, role->x, role->y, role->faceAngle + 2 * pa);
				bollAdd(role->boll, role, role->x, role->y, role->faceAngle - pa);
				bollAdd(role->boll, role, role->x, role->y, role->faceAngle - 2 * pa);
				ai->attackCount--;
			} else {
				// 3次扇形攻击后环形攻击。
				roleStopAttack(role);
			}
		} else if (role->attackingT == 0) {
			roleStopAttack(role);
			ai->state = AIFlameM_Circle;
		}
		break;
	case AIFlameM_Circle:
		role->faceAngle = aiGetAngleToEnemy(role, 0);
		for (double a = 3 * pa, max = 2 * M_PI - a; a < max; a += pa) {
			bollAdd(role->boll, role, role->x, role->y, role->faceAngle + a);
		}
		// 攻击结束，继续移动。
		aiFlameMInit(ai);
		break;
	default:
		break;
	}
}
