#ifndef _AI_FLAMEM_H_
#define _AI_FLAMEM_H_

#include <base.h>

#include "../../role.h"

// 炎兽的状态
enum AIFlameMState {
	AIFlameM_Idle,	  // 休息
	AIFlameM_Attack,  // 攻击
	AIFlameM_Circle,  // 环形弹幕
};

// 炎兽的实时ai数据
typedef struct _AIFlameM {
	struct _Role *role;

	enum AIFlameMState state;  // 状态。
	double turnAIT;			   // 转向倒计时。
	double attackAIT;		   // 攻击计划倒计时。
	int attackCount;		   // 攻击剩余计数。
} AIFlameM;

AIFlameM *aiFlameMCreate(struct _Role *role);
void aiFlameMDispose(AIFlameM *ai);
void aiFlameMUpdate(AIFlameM *ai, double t);

#endif