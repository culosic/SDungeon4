#ifndef _AI_TORTOISE_H_
#define _AI_TORTOISE_H_

#include <base.h>

#include "../../role.h"

// 玄龟的状态
enum AITortoiseState {
	AITortoise_Move,	 // 移动
};

// 玄龟的实时ai数据
typedef struct _AITortoise {
	struct _Role *role;

	enum AITortoiseState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
} AITortoise;

AITortoise *aiTortoiseCreate(struct _Role *role);
void aiTortoiseDispose(AITortoise *ai);
void aiTortoiseUpdate(AITortoise *ai, double t);

#endif