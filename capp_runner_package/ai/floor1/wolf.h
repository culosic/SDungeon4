#ifndef _AI_WOLF_H_
#define _AI_WOLF_H_

#include <base.h>

#include "../../role.h"

// 狼的状态
enum AIWolfState {
	AIWolf_Move,	// 移动
	AIWolf_Charge,	// 蓄力
	AIWolf_Attack,	// 扑咬
};

// 狼的实时ai数据
typedef struct _AIWolf {
	struct _Role *role;

	enum AIWolfState state;	 // 状态。
	double turnAIT;			 // 转向倒计时。
	double chargeT;			 // 蓄力倒计时。
	double attackDirection;	 // 攻击角度
	double attackAIT;		 // 攻击计划倒计时。
	double attackT;			 // 攻击耗能倒计时。
} AIWolf;

AIWolf *aiWolfCreate(struct _Role *role);
void aiWolfDispose(AIWolf *ai);
void aiWolfUpdate(AIWolf *ai, double t);

#endif