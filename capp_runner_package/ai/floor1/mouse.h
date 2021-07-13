#ifndef _AI_MOUSE_H_
#define _AI_MOUSE_H_

#include <base.h>

#include "../../role.h"

// 鼠的状态
enum AIMouseState {
	AIMouse_Move,	 // 移动
	AIMouse_Attack,	 // 攻击
};

// 鼠的实时ai数据
typedef struct _AIMouse {
	struct _Role *role;

	enum AIMouseState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
} AIMouse;

AIMouse *aiMouseCreate(struct _Role *role);
void aiMouseDispose(AIMouse *ai);
void aiMouseUpdate(AIMouse *ai, double t);

#endif