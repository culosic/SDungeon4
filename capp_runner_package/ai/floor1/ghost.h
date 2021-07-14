#ifndef _AI_GHOST_H_
#define _AI_GHOST_H_

#include <base.h>

#include "../../role.h"

// 鬼的状态
enum AIGhostState {
	AIGhost_Move,	 // 移动
	AIGhost_Attack,	 // 攻击
	AIGhost_State2,	 // 第二阶段
};

// 鬼的实时ai数据
typedef struct _AIGhost {
	struct _Role *role;

	enum AIGhostState state;  // 状态。
	double turnAIT;			  // 转向倒计时。
	double attackAIT;		  // 攻击计划倒计时。
	int attackCount;		  // 攻击剩余计数。
	double childT;			  // 生成小鬼倒计时。
	double childCDT;		  // 生成小鬼计CD。
} AIGhost;

AIGhost *aiGhostCreate(struct _Role *role);
void aiGhostDispose(AIGhost *ai);
void aiGhostUpdate(AIGhost *ai, double t);

///////////////////////////////////////////////////////////////

// 鬼首领的状态
enum AIGhostMainState {
	AIGhostMain_Move,	 // 移动
	AIGhostMain_Attack,	 // 攻击
};

// 鬼首领的实时ai数据
typedef struct _AIGhostMain {
	struct _Role *role;

	enum AIGhostMainState state;  // 状态。
	double turnAIT;				  // 转向倒计时。
	double attackAIT;			  // 攻击计划倒计时。
	double attackT;				  // 攻击耗能倒计时。
} AIGhostMain;

AIGhostMain *aiGhostMainCreate(struct _Role *role);
void aiGhostMainDispose(AIGhostMain *ai);
void aiGhostMainUpdate(AIGhostMain *ai, double t);

///////////////////////////////////////////////////////////////

// 小鬼的状态
enum AIGhostChildState {
	AIGhostChild_Move,	  // 移动
	AIGhostChild_Attack,  // 攻击
};

// 小鬼的实时ai数据
typedef struct _AIGhostChild {
	struct _Role *role;

	enum AIGhostChildState state;  // 状态。
	double turnAIT;				   // 转向倒计时。
	double attackAIT;			   // 攻击计划倒计时。
} AIGhostChild;

AIGhostChild *aiGhostChildCreate(struct _Role *role);
void aiGhostChildDispose(AIGhostChild *ai);
void aiGhostChildUpdate(AIGhostChild *ai, double t);

#endif