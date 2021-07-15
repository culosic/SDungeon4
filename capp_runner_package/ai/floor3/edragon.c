#include "edragon.h"

#include <base.h>
#include <ex_math.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../../room.h"
#include "../ai.h"

static void aiEdragonInit(AIEdragon *ai) {
	Role *role = ai->role;
	ai->state = AIEdragon_Move;
	ai->attackAIT = 0;
	ai->attackCount = 10;
	roleStopAttack(role);
	roleMove(role, getRandAngle());
}

AIEdragon *aiEdragonCreate(Role *role) {
	AIEdragon *ai = create(sizeof(AIEdragon));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff000000;
	boll->r = 10;
	boll->v = 400;
	aiEdragonInit(ai);
	return ai;
}

void aiEdragonDispose(AIEdragon *ai) {
	dispose(ai);
}

void aiEdragonUpdate(AIEdragon *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AIEdragon_Move:
		if (ai->attackAIT > 0) {
			ai->attackAIT -= t;
		} else {
			// 切换到攻击状态。
			ai->state = AIEdragon_Attack;
			ai->attackAIT = 0;
		}
		break;
	case AIEdragon_Attack:
		if (ai->attackCount > 0) {
			if (role->attackingT == 0) {
				roleAttack(role, aiGetAngleToEnemy(role, 0));
				float angle = role->faceAngle;
				for (int i = 0; i < 7; i++) {
					angle += M_PI / 4;
					bollAdd(role->boll, role, role->x, role->y, angle);
				}
				ai->attackCount--;
			} else {
				roleStopAttack(role);
			}
		} else {
			// 攻击结束，继续移动。
			aiEdragonInit(ai);
		}
		break;
	case AIEdragon_State2:
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->turnAIT > 0) {
		ai->turnAIT -= t;
	} else {
		ai->turnAIT = 0.4;
		roleMove(role, aiGetAngleToEnemy(role, 0));
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, 0));
		}
	}
}
