#include "game.h"

#include "base.h"
#include "cirpad.h"
#include "exb.h"
#include "global.h"
#include "map.h"
#include "role.h"

void gameDrawFPS(float t) {
	char s[20];
	game.fpsDT += t;
	if (game.fps < 1 || game.fpsDT > 1) {
		game.fpsDT = 0;
		game.fps = 1.0 / t;
	}
	sprintf(s, "FPS %.1f  SCR %d*%d", game.fps, SCRW, SCRH);
	drawTextC(s, 0, 0, 400, 60, 255, 255, 255, 30);
}

void gameUserControll(float t) {
	Cirpad *dpad = game.dpad;
	Cirpad *apad = game.apad;
	Role *role = game.role;
	cirpadUpdate(dpad, t);
	cirpadUpdate(apad, t);
	if (dpad->dragged) {
		roleMove(role, dpad->angle);
	} else {
		roleStopMove(role);
	}
	if (apad->active) {
		roleAttack(role, role->faceAngle);
	} else {
		roleStopAttack(role);
	}
}

void gameUpdate(long data) {
	int32 now = getuptime();
	float t = (now - game.drawLastTime) / 1000.0;
	game.drawLastTime = now;

	// 逻辑
	gameUserControll(t);
	roleUpdate(game.role, t);

	// 绘图
	cls(40, 50, 60);
	// mapDraw(game.map);
	mapDrawRoom(game.map);
	roleDraw(game.role);
	cirpadDraw(game.dpad);
	cirpadDraw(game.apad);
	gameDrawFPS(t);
	ref(0, 0, SCRW, SCRH);
}

void gameEvent(int type, int p, int q) {
	int result = false;
	if (!result) {
		result |= cirpadEvent(game.dpad, type, p, q);
		result |= cirpadEvent(game.apad, type, p, q);
	}
}

void gameInit() {
	if (SCRW > SCRH) {	// 横屏
		setscrsize(STAGEH * SCRW / SCRH, STAGEH);
	} else {  // 竖屏
		setscrsize(STAGEH, STAGEH * SCRH / SCRW);
	}
	game.map = mapCreate(60);
	game.role = roleCreate(game.map->currentRoom, 100, 100);
	game.dpad = cirpadCreate(200, SCRH - 200, 120, 40, false);
	game.apad = cirpadCreate(SCRW - 200, SCRH - 200, 120, 40, true);
	game.drawTimer = timercreate();
	timerstart(game.drawTimer, 1000 / FPS, 0, gameUpdate, 1);
	game.drawLastTime = getuptime();
}

void gameDispose() {
	timerstop(game.drawTimer);
	cirpadDispose(game.dpad);
	cirpadDispose(game.apad);
	roleDispose(game.role);
	mapDispose(game.map);
}
