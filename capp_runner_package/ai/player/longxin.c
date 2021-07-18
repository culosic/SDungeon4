#include "longxin.h"

#include <base.h>
#include <math.h>

#include "../../boll.h"
#include "../../data.h"
#include "../../global.h"
#include "../../role.h"
#include "../ai.h"

static void aiLongxinInit(AILongxin *ai) {
}

AILongxin *aiLongxinCreate(Role *role) {
	AILongxin *ai = create(sizeof(AILongxin));
	BollData *boll = role->boll->data;
	ai->role = role;
	// TODO 临时处理，设置子弹颜色，实际子弹颜色应该由武器决定。
	boll->color = 0xffb3e5fc;
	boll->r = 6;
	boll->v = 500;
	aiLongxinInit(ai);
	return ai;
}

void aiLongxinDispose(AILongxin *ai) {
	dispose(ai);
}

void aiLongxinUpdate(AILongxin *ai, double t) {
}
