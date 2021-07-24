#ifndef _AI_LONGXIN_H_
#define _AI_LONGXIN_H_

#include <base.h>

#include "../../role.h"

// 鼠的实时ai数据
typedef struct _AILongxin {
	struct _Role *role;

	// 符印加成等级
	int hpLevel; // 生命加成等级
	int atkLevel;
	int atkvLevel;
	int vLevel;
	int extLevel; // 额外弹道等级

	int extraAtkC; // 特殊符印：额外弹道数目
	int extraAtkCT; // 额外弹道计数，每隔若干次攻击，就会发射额外的弹幕。
} AILongxin;

AILongxin *aiLongxinCreate(struct _Role *role);
void aiLongxinDispose(AILongxin *ai);
void aiLongxinUpdate(AILongxin *ai, double t);

#endif