#include "game.h"

#include "base.h"
#include "exb.h"
#include "map.h"
#include "role.h"

// 逻辑运算相关
void gameLogic(float t) {
	roleUpdate(game.role, t);
}

void gameDrawFPS(float t) {
	char s[20];
	game.fpsDT += t;
	if (game.fps < 1 || game.fpsDT > 1) {
		game.fpsDT = 0;
		game.fps = 1.0 / t;
	}
	sprintf(s, "FPS %.1f", game.fps);
	drawTextC(s, 0, 0, 150, 60, 255, 255, 255, 30);
}

void gameUpdate(long data) {
	int32 now = getuptime();
	float t = (now - game.drawLastTime) / 1000.0;
	game.drawLastTime = now;

	// 逻辑
	gameLogic(t);

	// 绘图
	cls(40, 50, 60);
	// mapDraw(game.map);
	mapDrawRoom(game.map);
	roleDraw(game.role);
	gameDrawFPS(t);
	ref(0, 0, SCRW, SCRH);
}

void gameEvent(int type, int p, int q) {
	roleEvent(game.role, type, p, q);
}

void gameInit() {
	setscrsize(SCRWM, SCRWM * SCRH / SCRW);
	setpadtype(2);
	setTextSize(0, 14);
	game.map = mapCreate(60);
	game.role = roleCreate(game.map->currentRoom, 100, 100);
	game.drawTimer = timercreate();
	timerstart(game.drawTimer, 1000 / FPS, 0, &gameUpdate, 1);
	game.drawLastTime = getuptime();
}

void gameDispose() {
	timerstop(game.drawTimer);
	roleDispose(game.role);
	mapDispose(game.map);
}
