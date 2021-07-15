#ifndef _AI_ANT_H_
#define _AI_ANT_H_

#include <base.h>

#include "../../role.h"

// 蚂蚁的状态
enum AIAntState {
	AIAnt_Move,	 // 移动
	AIAnt_Attack,	 // 攻击
};

// 蚂蚁的实时ai数据
typedef struct _AIAnt {
	struct _Role *role;

	enum AIAntState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
} AIAnt;

AIAnt *aiAntCreate(struct _Role *role);
void aiAntDispose(AIAnt *ai);
void aiAntUpdate(AIAnt *ai, double t);

#endif