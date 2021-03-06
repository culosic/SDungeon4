#include "global.h"

#include <base.h>
#include <exb.h>
#include <graphics.h>
#include <math.h>

void* create(int32 size) {
	create_times++;
	void* memory = malloc(size);
	memset(memory, 0, size);
	return memory;
}

void dispose(void* address) {
	dispose_times++;
	free(address);
}

static void getRGB3Color(int32 color, uint8* r, uint8* g, uint8* b) {
	*r = (color & 0x00ff0000) >> 16;
	*g = (color & 0x0000ff00) >> 8;
	*b = color & 0x000000ff;
}

// static int32 getRGB(int r, int g, int b) {
// 	return 0xff000000 + (r << 24) + (g << 16) + b;
// }

char* utf8_c(char* c) {
	return ex_coding(c, strlen(c) + 1, "utf-8", "gb2312");
}

void drawText(char* c, int x, int y, int32 color, int textSize) {
	uint8 r, g, b;
	getRGB3Color(color, &r, &g, &b);
	setTextSize(1, textSize);
	dtext(c, x, y, r, g, b, 0, 1);
}

void drawTextC(char* c, int x, int y, int w, int h, int r, int g, int b, int textSize) {
	long fw = 0;
	long fh = 0;
	setTextSize(1, textSize);
	textwh(c, 1, 1, &fw, &fh);
	fw = fmax(fw, sizeof(*c) / 2 * textSize);
	dtext(c, x + (w - fw) / 2, y + (h - fh) / 2 - textSize / 8, r, g, b, 0, 1);
}

void drawTextexC(char* c, int x, int y, int w, int h, int r, int g, int b, int indent, int padding, int textSize) {
	long fw = 0;
	long fh = 0;
	setTextSize(1, textSize);
	textwh(c, 1, 1, &fw, &fh);
	fw = fmax(fw, sizeof(*c) / 2 * textSize);
	colorst color = {r, g, b};
	rectst rect = {x + padding, y, w - padding * 2, h - padding * 2};
	dtextex(c, x + indent, y + padding, &rect, &color, 0, 1);
}

int32 getAlphaColor(int32 color, float alpha) {
	if (alpha == 0) {
		return 0x00000000;
	}
	if (alpha == 1) {
		return color;
	}
	int32 a = ((int)(255 * alpha)) << 24;
	return (color & a) + (color ^ 0xff000000);
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

float getRandAngle() {
	return rand() % (int)(M_PI * 2000000) / 1000000.0;
}

float getRandScatter(float angle) {
	if (!angle) {
		return 0;
	}
	return (rand() % 2 ? 1 : -1) * rand() % (int)(angle * 1000000) / 1000000.0;
}

float getRandFloat(float from, float to) {
	return from + rand() % (int)(to * 1000000) / 1000000.0;
}

int32 getShiningColor(int32 color1, int32 color2, double t, double duration) {
	double f = duration * 2;
	t = fmod(t, f);
	double theta = t < duration ? t / duration : 1 - (t - duration) / duration;
	uint8 r1, g1, b1, r2, g2, b2;
	getRGB3Color(color1, &r1, &g1, &b1);
	getRGB3Color(color2, &r2, &g2, &b2);
	uint8 r = r1 + (r2 - r1) * theta;
	uint8 g = g1 + (g2 - g1) * theta;
	uint8 b = b1 + (b2 - b1) * theta;
	return 0xff000000 + (r << 16) + (g << 8) + b;
}