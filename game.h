#ifndef _GAME_
#define _GAME_

#define FPS 60.0
#define SCRWM 800

#include "base.h"
#include "exb.h"
#include "map_draw.h"
#include "role_draw.h"

typedef struct _Game {
	int32 timer;
	struct _Map *map;
	struct _Role *role;
} Game;

Game game;

void gameUpdate(long data) {
	cls(40, 50, 60);
	mapDraw(game.map);
	mapDrawRoom(game.map);
	roleDraw(game.role, 300, 300);
	ref(0, 0, SCRW, SCRH);
}

void gameInit() {
	setscrsize(SCRWM, SCRWM * SCRH / SCRW);
	setTextSize(0, 14);
	game.map = mapInit(60);
	game.role = roleInit(0, 0);
	game.timer = timercreate();
	timerstart(game.timer, 1000 / FPS, 0, &gameUpdate, 1);
}

void gameDispose() {
	timerstop(game.timer);
	mapDispose(game.map);
}

#endif