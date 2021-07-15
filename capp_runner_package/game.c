#include "game.h"

#include <base.h>
#include <exb.h>

#include "cirpad.h"
#include "data.h"
#include "global.h"
#include "map.h"
#include "role.h"

static void gameDrawFPS(float t) {
	char s[50];
	game.fpsDT += t;
	if (game.fps < 1 || game.fpsDT > 1) {
		game.fpsDT = 0;
		game.fps = 1.0 / t;
	}
	sprintf(s, "FPS %.1f  SCR %d*%d", game.fps, SCRW, SCRH);
	drawTextC(s, 0, 0, 400, 60, 255, 255, 255, 30);
}

static void gameUserControll(float t) {
	Cirpad *dpad = game.dpad;
	Cirpad *apad = game.apad;
	Role *role = game.mainRole;
	cirpadUpdate(dpad, t);
	cirpadUpdate(apad, t);
	if (dpad->dragged) {
		roleMove(role, dpad->angle);
	} else {
		roleStopMove(role);
	}
	if (apad->active) {
		Role *cloestEnemy = roomGetCloestEnemy(role->room, role);
		double angle = cloestEnemy ? getAngle(role->x, role->y, cloestEnemy->x, cloestEnemy->y) : role->faceAngle;
		roleAttack(role, angle);
	} else {
		roleStopAttack(role);
	}
}

void gameUpdate(long data) {
	int32 now = getuptime();
	float t = (now - game.drawLastTime) / 1000.0;
	game.drawLastTime = now;

	// 逻辑
	mapUpdate(game.map, t);
	gameUserControll(t);

	// 绘图
	cls(40, 50, 60);
	mapDraw(game.map, t);
	mapDrawMiniMap(game.map, t);
	cirpadDraw(game.dpad, t);
	cirpadDraw(game.apad, t);
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
	cls(40, 50, 60);
	ref(0, 0, SCRW, SCRH);
	if (SCRW > SCRH) {	// 横屏
		setscrsize(STAGEH * SCRW / SCRH, STAGEH);
	} else {  // 竖屏
		setscrsize(STAGEH, STAGEH * SCRH / SCRW);
	}
	Map *map = game.map = mapCreate();
	Role *mainRole = game.mainRole = roleCreate(RoleType_LongXin, false, false);
	Room *initRoom = map->currentRoom;
	Room *lastRoom = map->roomList[1];
	roomAddRole(initRoom, mainRole, 100, 400);

	// // 第一层敌人测试
	// roomAddRole(initRoom, roleCreate(RoleType_Mouse, true, true), 300, 100);
	// roomAddRole(initRoom, roleCreate(RoleType_Wolf, true, true), 400, 200);
	// roomAddRole(initRoom, roleCreate(RoleType_Scorpion, true, true), 400, 300);
	// // 第一层boss测试
	// roomAddRole(lastRoom, roleCreate(RoleType_Ghost, true, true), 400, 400);

	// 第二层敌人测试
	roomAddRole(initRoom, roleCreate(RoleType_Ant, true, true), 300, 100);
	roomAddRole(initRoom, roleCreate(RoleType_Frog, true, true), 400, 200);
	roomAddRole(initRoom, roleCreate(RoleType_Snake, true, true), 400, 300);
	// 第二层boss测试
	roomAddRole(lastRoom, roleCreate(RoleType_FlameM, true, true), 400, 400);

	// // 第三层敌人测试
	// roomAddRole(initRoom, roleCreate(RoleType_Bee, true, true), 300, 100);
	// roomAddRole(initRoom, roleCreate(RoleType_Tiger, true, true), 400, 200);
	// roomAddRole(initRoom, roleCreate(RoleType_Tortoise, true, true), 400, 300);
	// // 第三层boss测试
	// roomAddRole(lastRoom, roleCreate(RoleType_EDragon, true, true), 400, 400);

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
	mapDispose(game.map);
	printf(utf8_c("内存释放情况：%d/%d\n"), dispose_times, create_times);
}
