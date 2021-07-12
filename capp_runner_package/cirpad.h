#ifndef _CIRPAD_H_
#define _CIRPAD_H_

#include "base.h"
#include "role.h"

/**
 * @brief 一个简单的摇杆
 * 
 * @author 火烧云
 * @since 2021年7月3日
 */

typedef struct _Cirpad {
	struct _Role *role;
	float x;
	float y;
	float r;
	float barX;
	float barY;
	float barR;
	float activeR;
	int justTouch;

	double angle;
	int active;	 // 是否在挪动或点击摇杆
	int activeI;
	int dragged;  // 摇杆是否被有效挪动，此时会产生摇杆挪动事件，比如移动角色等。
} Cirpad;

Cirpad *cirpadCreate(float x, float y, float r, float r2, int justTouch);
void cirpadDispose(Cirpad *cirpad);
void cirpadUpdate(Cirpad *pad, double t);
void cirpadDraw(Cirpad *cirpad, double t);
int cirpadEvent(Cirpad *cirpad, int type, int p, int q);

#endif