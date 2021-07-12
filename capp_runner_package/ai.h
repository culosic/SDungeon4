#ifndef _AI_H_
#define _AI_H_

#include "base.h"
#include "role.h"

enum AIMouseState {
	AIMouse_Slow,	 // 慢速移动
	AIMouse_Rush,	 // 高速移动
	AIMouse_Attack,	 // 攻击
};

typedef struct _AIMouse {
	struct _Role *role;

	enum AIMouseState state;  // 状态。
	double direction;		  // 当前朝向。 TODO 改为攻击方向
	double tureCDT;			  // 转向CD。
	double rushCDT;			  // 冲刺冷却计时。
	double rushAIT;			  // 冲刺计划倒计时。

	double rushT;	  // 高速移动计时。
	int attackCount;  // 高速移动后攻击计数。
} AIMouse;

AIMouse *aiMouseCreate(struct _Role *role);
void aiMouseDispose(AIMouse *ai);
void aiMouseUpdate(AIMouse *ai, double t);

#endif