#ifndef _ROLE_DRAW_H_
#define _ROLE_DRAW_H_

#include "base.h"
#include "c/role.h"
#include "exb.h"
#include "graphics.h"

void roleDraw(Role* role, float x, float y) {
	int r = 20;
	int rb = 2;
	x += role->x;
	y += role->y;
	drawCir(x, y, r + rb * 2, 0xff009688);
	drawCir(x, y, r, 0x77005737);
	drawTextC(utf8_c("我"), x - r, y - r, r * 2, r * 2, 225, 225, 245, 20);
}

#endif