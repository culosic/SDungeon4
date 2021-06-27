#ifndef _ROOM_DRAW_H_
#define _ROOM_DRAW_H_

#include "base.h"
#include "c/room.h"
#include "exb.h"
#include "graphics.h"

void roomDraw(Room* room) {
	int x = room->px;
	int y = room->py;
	int fcolor = 0xff696969;
	int wcolor = 0xffa9a9a9;
	int dcolor = 0xff795548;
	for (int i = 0; i < room->tileCount; i++) {
		RoomTile* tile = room->tiles[i];
		switch (tile->type) {
		case RoomTile_Floor:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, fcolor);
			drawTextC(tile->caption, x + tile->x, y + tile->y, tile->w, tile->h, 90, 90, 90, 120);
			break;
		case RoomTile_Wall:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, wcolor);
			break;
		case RoomTile_Door:
			drawRect(x + tile->x, y + tile->y, tile->w, tile->h, dcolor);
			break;
		default:
			break;
		}
	}
}

#endif