#include "cirpad.h"

#include <base.h>
#include <ex_math.h>
#include <exb.h>
#include <graphics.h>
#include <math.h>

#include "global.h"

Cirpad *cirpadCreate(float x, float y, float r, float barR, int justTouch) {
	Cirpad *pad = create(sizeof(struct _Cirpad));
	pad->x = x;
	pad->y = y;
	pad->r = r;
	pad->barX = x;
	pad->barY = y;
	pad->barR = barR < r ? barR : r / 3;
	pad->activeR = justTouch ? r * 0.7 : r;
	pad->justTouch = justTouch;
	return pad;
}

void cirpadDispose(Cirpad *pad) {
	dispose(pad);
}

void cirpadUpdate(Cirpad *pad, double t) {
	int oldActive = pad->active;
	int up = true;
	for (int i = 0; i < 5; i++) {  // 多点触控
		if (!touch_isdown(i)) {
			continue;
		}
		int x = touch_getx(i);
		int y = touch_gety(i);
		float dist = getLineSize(pad->x, pad->y, x, y);
		if (dist <= pad->activeR) {
			up = false;
			pad->active = true;
			pad->activeI = i;
		}
		if (!pad->justTouch && pad->active && pad->activeI == i) {
			up = false;
			if (dist > pad->barR) {	 // 摇杆移动生效
				pad->dragged = true;
				pad->angle = getAngle(pad->x, pad->y, x, y);
			}
			if (dist <= pad->activeR) {	 // 摇杆在范围内拖拽
				pad->barX = x;
				pad->barY = y;
			} else {  // 摇杆拖拽到范围外，仍显示到范围内。
				pad->barX = pad->x + pad->activeR * cos(pad->angle);
				pad->barY = pad->y + pad->activeR * sin(pad->angle);
			}
		}
	}
	if (oldActive && up) {
		pad->active = false;
		if (!pad->justTouch) {
			pad->dragged = false;
			pad->barX = pad->x;
			pad->barY = pad->y;
		}
	}
}

void cirpadDraw(Cirpad *pad, double t) {
	if (pad->justTouch) {
		drawCir(pad->x, pad->y, pad->activeR, pad->active ? 0x33ffffff : 0x22ffffff);
		drawCir(pad->x, pad->y, pad->activeR * 0.85, pad->active ? 0xaaffffff : 0x66ffffff);
	} else {
		drawCir(pad->x, pad->y, pad->activeR, pad->active ? 0x33ffffff : 0x22ffffff);
		drawCir(pad->barX, pad->barY, pad->barR, pad->active ? 0xccffffff : 0x66ffffff);
	}
}

int cirpadEvent(Cirpad *pad, int type, int p, int q) {
	return !pad->active;
}
