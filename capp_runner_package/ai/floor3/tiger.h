#ifndef _AI_TIGER_H_
#define _AI_TIGER_H_

#include <base.h>

#include "../../role.h"

// 虎拳的状态
enum AITigerState {
	AITiger_Move,	// 移动
	AITiger_Charge,	// 蓄力
	AITiger_Attack,	// 扑咬
};

// 虎拳的实时ai数据
typedef struct _AITiger {
	struct _Role *role;

	enum AITigerState state;	 // 状态。
	double turnAIT;			 // 转向倒计时。
	double chargeT;			 // 蓄力倒计时。
	double attackDirection;	 // 攻击角度
	double attackAIT;		 // 攻击计划倒计时。
	double attackT;			 // 攻击耗能倒计时。
} AITiger;

AITiger *aiTigerCreate(struct _Role *role);
void aiTigerDispose(AITiger *ai);
void aiTigerUpdate(AITiger *ai, double t);

#endif