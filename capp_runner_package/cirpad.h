#ifndef _CIRPAD_H_
#define _CIRPAD_H_
/**
 * @brief 一个简单的摇杆
 * 
 * @author 火烧云
 * @since 2021年7月3日
 */

typedef struct _Cirpad {
	float x;
	float y;
	float r;
	float r2;
	double angle;
} Cirpad;

Cirpad cirpadCreate(float x, float y, float r, float r2);
void cirpadDispose(Cirpad *cirpad);
void cirpadUpdate(Cirpad *cirpad, double dt);
void cirpadDraw(Cirpad *cirpad);
int cirpadEvent(Cirpad *cirpad);

#endif