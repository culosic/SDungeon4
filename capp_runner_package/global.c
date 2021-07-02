#include "global.h"

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
