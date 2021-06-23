#ifndef _ROOM_DRAW_H_
#define _ROOM_DRAW_H_

#include "base.h"
#include "c/room.h"
#include "exb.h"
#include "graphics.h"

void roomDraw(Room* room) {
	//todo 绘制地面，墙体，人物在地图移动，
	int x = 150;
	int y = 1100;
	int w = 500;
	int h = 500;
	int d = 30;
	int doorw = 50;
	int wcolor = 0xffa9a9a9;
	int fcolor = 0xff696969;
	int dcolor = 0xff795548;
	// 画地面
	drawRect(x, y, w, h, fcolor);
	// 画墙体
	drawRect(x - d, y - d, w + d * 2, d, wcolor);
	drawRect(x + w, y - d, d, h + d * 2, wcolor);
	drawRect(x - d, y + h, w + d * 2, d, wcolor);
	drawRect(x - d, y - d, d, h + d * 2, wcolor);
	// 画门
	for (int i = 0; i < room->linkRoomCount; i++) {
		Room* linkRoom = room->linkRooms[i];
		if (room->x == linkRoom->x) {
			if (room->y > linkRoom->y) {
				//2
				drawRect(x + (w - doorw) / 2, y - d, doorw, d, dcolor);
			} else {
				//8
				drawRect(x + (w - doorw) / 2, y + h, doorw, d, dcolor);
			}
		} else if (room->y == linkRoom->y) {
			if (room->x > linkRoom->x) {
				// 4
				drawRect(x - d, y + (h - doorw) / 2, d, doorw, dcolor);
			} else {
				//6
				drawRect(x + w, y + (h - doorw) / 2, d, doorw, dcolor);
			}
		}
	}
}

#endif