#ifndef _ROLE_DRAW_H_
#define _ROLE_DRAW_H_

#include "base.h"
#include "c/role.h"
#include "exb.h"
#include "graphics.h"

void roleDraw(Role* role) {
	int r = 20;
	int rb = 2;
	Room* room = role->room;
	float x = room->px + role->x;
	float y = room->py + role->y;
	drawCir(x, y, r + rb * 2, 0xff009688);
	drawCir(x, y, r, 0x77005737);
	drawTextC(utf8_c("我"), x - r, y - r, r * 2, r * 2, 225, 225, 245, 20);

	char spd[30];
	sprintf(spd, "v=%.2f,d=%d", role->v, role->direction);
	drawTextC(spd, x - r, y - r * 2 - 10, r * 2, r * 2, 225, 225, 245, 20);
}

#endif