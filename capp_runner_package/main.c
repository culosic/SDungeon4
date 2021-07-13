/**
 * 程序名：S地牢0.4-传承
 * 说明：一个地牢探险游戏，最终目的是到达最深处，拿到被埋葬的圣人永炼-千刃的传承。相比0.3版本，地图生成比较简单，改战棋模式为即时战斗模式。
 * 作者：火烧云
 * QQ群：496717720
 * 时间：2021年6月18日
 */

#include <base.h>

#include "ai/ai.c"
#include "ai/floor1/mouse.c"
#include "ai/floor1/scorpion.c"
#include "ai/floor1/wolf.c"
#include "boll.c"
#include "cirpad.c"
#include "game.c"
#include "global.c"
#include "map.c"
#include "role.c"
#include "room.c"

int init() {
	gameInit();
	return 0;
}

int event(int type, int p1, int p2) {
	gameEvent(type, p1, p2);
	if (KY_UP == type) {
		switch (p1) {
		case _BACK:
			exit();
			break;

		case _MENU:
			break;
		}
	}

	return 0;
}

int pause() {
	return 0;
}

int resume() {
	return 0;
}

int exitApp() {
	gameDispose();
	return 0;
}