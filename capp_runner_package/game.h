#ifndef _GAME_H_
#define _GAME_H_

#include <base.h>

#include "cirpad.h"
#include "map.h"
#include "role.h"

#define FPS 60.0
#define STAGEH 800

// 场景类型
enum ScreenType {
	Screen_None,	// 空
	Screen_Init,	// 初始界面
	Screen_Down,	// 下楼
	Screen_Game,	// 游戏中
	Screen_Passed,	// 通关画面
};

// 结束演出场景
enum PassedScreenType {
	PassedScreen_None,
	PassedScreen_Story,
	PassedScreen_Fly,
	PassedScreen_Thanks,
};

typedef struct _Game {
	int32 drawTimer;
	int32 drawLastTime;
	float fpsDT;
	float fps;

	// 场景相关
	enum ScreenType screen;
	enum ScreenType nextScreen;
	double screenT;

	// 初始界面相关
	double logoT;

	// 下楼界面
	double downT;
	int floor;

	// 结束演出界面
	enum PassedScreenType passedScreenType;
	float passedFontAlphaT;
	float passedFontStayT;
	float passedRoleX;
	float passedRoleY;
	float passedRoleFz;
	double passedRoleT;
	double passedRoleRun;
	double passedRoleFly;
	double passedTextT;
	int passedTextIndex;
	int passedEnd;

	struct _Map *map;
	struct _Role *mainRole;
	struct _Cirpad *dpad;
	struct _Cirpad *apad;
} Game;

Game game;

void gameUpdate(long data);
void gameEvent(int type, int p, int q);
void gameInit();
void gameDispose();

#endif