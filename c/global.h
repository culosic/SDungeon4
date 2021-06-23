#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef CAPP
#include "base.h"
#include "exb.h"
#include "graphics.h"
#endif

#ifndef NULL
#define NULL((void*)0)
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifdef CAPP
char* utf8_c(char* c) {
	return ex_coding(c, sizeof(c), "utf-8", "gb2312");
}
#else
char* utf8_c(char* c) {
	return c;
}
#endif

#ifdef CAPP
void drawTextC(char* c, int x, int y, int w, int h, int r, int g, int b, int textSize) {
	long fw = 0;
	long fh = 0;
	setTextSize(1, textSize);
	textwh(c, 0, 1, &fw, &fh);
	//printf("textwh%d, %d\n", (int)fw, (int)fh);
	//drawRect(x+(w-fw)/2,y+(h-fh)/2, fw, fh, 0xff000000);
	dtext(c, x + (w - fw) / 2, y + (h - fh) / 2 - textSize / 8, r, g, b, 0, 1);
}
#endif

#endif