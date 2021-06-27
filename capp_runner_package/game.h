#ifndef _GAME_
#define _GAME_

#define FPS 60.0
#define SCRWM 800

#include "base.h"
#include "exb.h"
#include "map_draw.h"
#include "role_draw.h"

typedef struct _Game {
	int32 drawTimer;
	int32 drawLastTime;
	float fpsDT;
	float fps;
	struct _Map *map;
	struct _Role *role;
} Game;

Game game;

// 逻辑运算相关
void gameLogic(float t) {
	roleUpdate(game.role, t);
}

void gameDrawFPS(float t) {
	char s[20];
	game.fpsDT += t;
	if (game.fps < 1 || game.fpsDT > 1000) {
		game.fpsDT = 0;
		game.fps = 1.0 / t;
	}
	sprintf(s, "FPS %.1f", game.fps);
	drawTextC(s, 0, 0, 150, 60, 255, 255, 255, 30);
}

void gameUpdate(long data) {
	float t = (getuptime() - game.drawLastTime) / 1000.0;

	// 逻辑
	gameLogic(t);

	// 绘图
	cls(40, 50, 60);
	mapDraw(game.map);
	mapDrawRoom(game.map);
	roleDraw(game.role);
	gameDrawFPS(t);
	ref(0, 0, SCRW, SCRH);

	game.drawLastTime = getuptime();
}

void gameEvent(int type, int p, int q) {
	roleEvent(game.role, type, p, q);
}

void gameInit() {
	setscrsize(SCRWM, SCRWM * SCRH / SCRW);
	setpadtype(2);
	setTextSize(0, 14);
	game.map = mapInit(60);
	game.role = roleInit(game.map->currentRoom, 100, 100);
	game.drawTimer = timercreate();
	timerstart(game.drawTimer, 1000 / FPS, 0, &gameUpdate, 1);
	game.drawLastTime = getuptime();
}

void gameDispose() {
	timerstop(game.drawTimer);
	mapDispose(game.map);
}

#endif