#ifndef _AI_BEE_H_
#define _AI_BEE_H_

#include <base.h>

#include "../../role.h"

// 蜂的状态
enum AIBeeState {
	AIBee_Move,	 // 移动
	AIBee_Attack,	 // 攻击
};

// 蜂的实时ai数据
typedef struct _AIBee {
	struct _Role *role;

	enum AIBeeState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
} AIBee;

AIBee *aiBeeCreate(struct _Role *role);
void aiBeeDispose(AIBee *ai);
void aiBeeUpdate(AIBee *ai, double t);

#endif