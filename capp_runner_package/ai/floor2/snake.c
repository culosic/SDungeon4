#include "snake.h"

#include <base.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiSnakeInit(AISnake *ai) {
	Role *role = ai->role;
	ai->state = AISnake_Idle;
	ai->attackAIT = 3;
	ai->attackCount = 6;
	roleStopAttack(role);
}

AISnake *aiSnakeCreate(Role *role) {
	AISnake *ai = create(sizeof(AISnake));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff800000;
	boll->r = 5;
	boll->v = 200;
	aiSnakeInit(ai);
	return ai;
}

void aiSnakeDispose(AISnake *ai) {
	dispose(ai);
}

void aiSnakeUpdate(AISnake *ai, double t) {
	Role *role = ai->role;
	// 更新状态机：攻击=>等待=>再次攻击...
	switch (ai->state) {
	case AISnake_Idle:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AISnake_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AISnake_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, M_PI / 12));
				bollAdd(role->boll, role, role->x, role->y, aiGetAngleToEnemy(role, M_PI / 12));
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiSnakeInit(ai);
		}
		break;
	default:
		break;
	}
}
