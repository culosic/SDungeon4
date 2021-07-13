#ifndef _AI_SCORPION_H_
#define _AI_SCORPION_H_

#include <base.h>

#include "../../role.h"

// 蝎的状态
enum AIScorpionState {
	AIScorpion_Move,	 // 移动
	AIScorpion_Attack,	 // 攻击
};

// 蝎的实时ai数据
typedef struct _AIScorpion {
	struct _Role *role;

	enum AIScorpionState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
} AIScorpion;

AIScorpion *aiScorpionCreate(struct _Role *role);
void aiScorpionDispose(AIScorpion *ai);
void aiScorpionUpdate(AIScorpion *ai, double t);

#endif