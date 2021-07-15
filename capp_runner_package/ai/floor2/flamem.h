#ifndef _AI_FLAMEM_H_
#define _AI_FLAMEM_H_

#include <base.h>

#include "../../role.h"

// 炎兽的状态
enum AIFlameMState {
	AIFlameM_Move,	  // 移动
	AIFlameM_Attack,  // 攻击
	AIFlameM_State2,  // 第二阶段
};

// 炎兽的实时ai数据
typedef struct _AIFlameM {
	struct _Role *role;

	enum AIFlameMState state;  // 状态。
	double turnAIT;			   // 转向倒计时。
	double attackAIT;		   // 攻击计划倒计时。
	int attackCount;		   // 攻击剩余计数。
	double childT;			   // 生成小鬼倒计时。
	double childCDT;		   // 生成小鬼计CD。
} AIFlameM;

AIFlameM *aiFlameMCreate(struct _Role *role);
void aiFlameMDispose(AIFlameM *ai);
void aiFlameMUpdate(AIFlameM *ai, double t);

#endif