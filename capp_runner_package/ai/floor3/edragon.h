#ifndef _AI_EDRAGON_H_
#define _AI_EDRAGON_H_

#include <base.h>

#include "../../role.h"

// 纯阴·地龙的状态
enum AIEdragonState {
	AIEdragon_Move,	   // 移动
	AIEdragon_Attack,  // 攻击
	AIEdragon_State2,  // 第二阶段
};

// 纯阴·地龙的实时ai数据
typedef struct _AIEdragon {
	struct _Role *role;

	enum AIEdragonState state;	// 状态。
	double turnAIT;				// 转向倒计时。
	double attackAIT;			// 攻击计划倒计时。
	int attackCount;			// 攻击剩余计数。
} AIEdragon;

AIEdragon *aiEdragonCreate(struct _Role *role);
void aiEdragonDispose(AIEdragon *ai);
void aiEdragonUpdate(AIEdragon *ai, double t);

#endif