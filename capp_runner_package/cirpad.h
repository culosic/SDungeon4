#ifndef _CIRPAD_H_
#define _CIRPAD_H_

#include <base.h>

#include "role.h"

/**
 * @brief 一个简单的摇杆
 * 
 * @author 火烧云
 * @since 2021年7月3日
 */

typedef struct _Cirpad {
	struct _Role *role;
	float x;  // 摇杆区域显示位置
	float y;
	float r;
	float barX;	 // 摇杆杆柄位置（就是中心的那个可拖动的圆形）
	float barY;
	float barR;
	float activeR;	// 摇杆事件响应半径（在这个半径区域内按下屏幕，才可以拖动，或者点击）
	int justTouch;	// TRUE：仅点击，FALSE：摇杆。

	double angle;  // 摇杆拖动方向
	int active;	   // 是否在挪动或点击摇杆
	int activeI;   // 表示触发摇杆的事件，是多点触控的第几个点
	int dragged;   // 摇杆是否被有效挪动，此时会产生摇杆挪动事件，比如移动角色等。
} Cirpad;

Cirpad *cirpadCreate(float x, float y, float r, float r2, int justTouch);
void cirpadDispose(Cirpad *cirpad);
void cirpadUpdate(Cirpad *pad, double t);
void cirpadDraw(Cirpad *cirpad, double t);
int cirpadEvent(Cirpad *cirpad, int type, int p, int q);

#endif