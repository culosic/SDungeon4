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
	boll->v = 600;
	ai->extraAtkC = 1;
	aiLongxinInit(ai);
	return ai;
}

void aiLongxinDispose(AILongxin *ai) {
	dispose(ai);
}

void aiLongxinUpdate(AILongxin *ai, double t) {
	Role *role = ai->role;
	if (role->attacking && role->attackingT == 0) {
		if (ai->extraAtkCT < 3) {
			ai->extraAtkCT++;
		} else {
			ai->extraAtkCT = 0;
			for (int i = 0; i < ai->extraAtkC; i++) {
				bollAdd(role->boll, role, role->x, role->y, role->faceAngle + getRandScatter(0.2));
			}
		}
	}
}

void aiLongxinAddLevel(AILongxin *ai, enum FuyinType type) {
	Role *role = ai->role;
	switch (type) {
	case Fuyin_HP:
		role->hps += longxin_level_hp[ai->hpLevel];
		role->hp += longxin_level_hp[ai->hpLevel];
		ai->hpLevel++;
		break;
	case Fuyin_Atk:
		role->atk += longxin_level_atk[ai->atkLevel];
		role->boll->data->r += longxin_level_atk[ai->atkLevel] + 1;
		ai->atkLevel++;
		break;
	case Fuyin_AtkV:
		role->atkv = role->boll->data->atkv = fmax(0.1, role->boll->data->atkv - longxin_level_atkv[ai->atkvLevel]);
		ai->atkvLevel++;
		break;
	case Fuyin_V:
		role->v += longxin_level_v[ai->vLevel];
		ai->vLevel++;
		break;
	case Fuyin_EXT:
		ai->extraAtkC += longxin_level_ext[ai->extLevel];
		ai->extLevel++;
		break;
	default:
		printf("Error addition level %d\n", type);
		break;
	}
}
