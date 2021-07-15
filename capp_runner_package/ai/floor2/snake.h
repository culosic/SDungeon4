#ifndef _AI_SNAKE_H_
#define _AI_SNAKE_H_

#include <base.h>

#include "../../role.h"

// 蛇的状态
enum AISnakeState {
	AISnake_Idle,	  // 站立
	AISnake_Attack,  // 攻击
};

// 蛇的实时ai数据
typedef struct _AISnake {
	struct _Role *role;

	enum AISnakeState state;  // 状态。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
} AISnake;

AISnake *aiSnakeCreate(struct _Role *role);
void aiSnakeDispose(AISnake *ai);
void aiSnakeUpdate(AISnake *ai, double t);

#endif