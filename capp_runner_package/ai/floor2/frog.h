#ifndef _AI_FROG_H_
#define _AI_FROG_H_

#include <base.h>

#include "../../role.h"

// 蛙的状态
enum AIFrogState {
	AIFrog_Idle,	// 站立
	AIFrog_Attack,	// 扑咬
};

// 蛙的实时ai数据
typedef struct _AIFrog {
	struct _Role *role;

	enum AIFrogState state;	 // 状态。
	double attackDirection;	 // 攻击角度
	double attackAIT;		 // 攻击计划倒计时。
	double attackT;			 // 攻击耗能倒计时。
} AIFrog;

AIFrog *aiFrogCreate(struct _Role *role);
void aiFrogDispose(AIFrog *ai);
void aiFrogUpdate(AIFrog *ai, double t);

#endif