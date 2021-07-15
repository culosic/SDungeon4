#include "tortoise.h"

#include <base.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiTortoiseInit(AITortoise *ai) {
	Role *role = ai->role;
	ai->state = AITortoise_Move;
	roleMove(role, getRandAngle());
}

AITortoise *aiTortoiseCreate(Role *role) {
	AITortoise *ai = create(sizeof(AITortoise));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xff6633aa;
	boll->r = 10;
	boll->v = 200;
	aiTortoiseInit(ai);
	return ai;
}

void aiTortoiseDispose(AITortoise *ai) {
	dispose(ai);
}

void aiTortoiseUpdate(AITortoise *ai, double t) {
	Role *role = ai->role;
	RoleData *data = role->data;
	Room *room = role->room;
	// 更新状态机：攻击=>移动片刻=>再次攻击...
	switch (ai->state) {
	case AITortoise_Move:
		break;
	default:
		break;
	}
	// 过一段时间就转向
	if (ai->turnAIT > 0) {
		ai->turnAIT -= t;
	} else {
		ai->turnAIT = 0.3;
		roleMove(role, aiGetAngleToEnemy(role, M_PI / 12));
	}
	// 碰撞墙壁，也需要转向
	if (role->vx != 0 && role->vy != 0) {
		RoomTile *tile = roomColl(room, role->x + role->vx * t, role->y + role->vy * t, data->r);
		if (tile) {
			role->v = data->v0;
			roleMove(role, aiGetAngleToEnemy(role, M_PI / 12));
		}
	}
}
