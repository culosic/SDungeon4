#ifndef _GAME_
#define _GAME_

#define FPS 60.0
#define SCRWM 800

#include "base.h"
#include "exb.h"
#include "map_draw.h"
#include "role_draw.h"

typedef struct _Game {
	int32 updateTimer;
	int32 drawTimer;
	int32 drawLastTime;
	float fpsDT;
	float fps;
	struct _Map *map;
	struct _Role *role;
} Game;

Game game;

// 逻辑运算相关
void gameUpdate(long data) {
	roleUpdate(game.role);
}

void gameDrawFPS() {
	char s[20];
	float delta = getuptime() - game.drawLastTime;
	game.fpsDT += delta;
	if (game.fps < 1 || game.fpsDT > 3000) {
		game.fpsDT = 0;
		game.fps = 1000 / delta;
	}
	sprintf(s, "FPS %.1f", game.fps);
	drawTextC(s, 0, 0, 150, 60, 255, 255, 255, 30);
}

// 绘制相关
void gameDraw(long data) {
	cls(40, 50, 60);
	mapDraw(game.map);
	mapDrawRoom(game.map);
	roleDraw(game.role, 300, 300);
	gameDrawFPS();
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
	game.role = roleInit(0, 0);
	game.updateTimer = timercreate();
	game.drawTimer = timercreate();
	timerstart(game.updateTimer, 1000 / FPS, 0, &gameUpdate, 1);
	timerstart(game.drawTimer, 1000 / FPS, 0, &gameDraw, 1);
}

void gameDispose() {
	timerstop(game.updateTimer);
	timerstop(game.drawTimer);
	mapDispose(game.map);
}

#endif