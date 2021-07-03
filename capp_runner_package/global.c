#include "global.h"

#include <math.h>

#include "base.h"
#include "exb.h"
#include "graphics.h"

char* utf8_c(char* c) {
	return ex_coding(c, sizeof(c), "utf-8", "gb2312");
}

void drawTextC(char* c, int x, int y, int w, int h, int r, int g, int b, int textSize) {
	long fw = 0;
	long fh = 0;
	setTextSize(1, textSize);
	textwh(c, 0, 1, &fw, &fh);
	dtext(c, x + (w - fw) / 2, y + (h - fh) / 2 - textSize / 8, r, g, b, 0, 1);
}

float getAngle(float x0, float y0, float x1, float y1) {
	float dx = x1 - x0, dy = y1 - y0;
	float r = 0;
	if (dx == 0) {	// y轴方向
		if (dy < 0) {
			r = M_PI * 0.5;
		} else if (dy > 0) {
			r = M_PI * 1.5;
		}
	} else if (dy == 0) {  // x轴方向
		if (dx > 0) {
			r = 0;
		} else if (dx < 0) {
			r = M_PI;
		}
	} else if (dy > 0) {  // 第一二象限
		r = dx > 0 ? atan(dy / dx) : (-atan(dx / dy) + M_PI * 0.5);
	} else {  // 第三四象限
		r = dx < 0 ? (atan(dy / dx) + M_PI) : (-atan(dx / dy) + M_PI * 1.5);
	}
	return r;
}