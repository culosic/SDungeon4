#ifndef _DRAW_H_
#define _DRAW_H_

#include "base.h"
#include "c/map.h"
#include "exb.h"
#include "graphics.h"

void mapDraw(Map* map, int x, int y) {
	setTextSize(1, 30);
	for (int i = 0; i < map->roomCount; i++) {
		Room* room = map->roomList[i];
		int x = room->x * 100;
		int y = room->y * 100;
		drawRect(x, y, 80, 80, 0xff334466);
		dtext(room->caption, x, y, 245, 245, 300, 0, 1);
	}
}

#endif