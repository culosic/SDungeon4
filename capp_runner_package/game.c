#include "game.h"

#include <android.h>
#include <base.h>
#include <ex_math.h>
#include <exb.h>
#include <graphics.h>
#include <math.h>

#include "cirpad.h"
#include "data.h"
#include "global.h"
#include "map.h"
#include "role.h"

// 过度页面
static void screenGotoNextUpdate(double t) {
	double T = 0.15;
	if (game.nextScreen != Screen_None) {  // 过度中
		if (game.screenT < T) {			   // 进入新页面
			game.screenT = fmin(game.screenT + t, T);
			drawRect(0, 0, SCRW, SCRH, getAlphaColor(0xff000000, game.screenT / T));
		} else {
			// 跳转到下一个页面
			if (game.nextScreen == Screen_Init || game.nextScreen == Screen_Passed) {  // 回到主菜单界面
				if (game.mainRole != NULL) {
					mapDispose(game.map);
					roleDispose(game.mainRole);
					game.map = NULL;
					game.mainRole = NULL;
					game.floor = 0;
					game.userControll = true;
					game.fail = false;
					game.failT = 0;
					game.passed = false;
					game.passedT = 0;
				}
				game.passedScreenType = PassedScreen_None;
			}
			game.screen = game.nextScreen;
			game.nextScreen = Screen_None;
			drawRect(0, 0, SCRW, SCRH, 0xff000000);
		}
	} else {
		if (game.screenT > 0) {
			game.screenT = fmax(0, game.screenT - t);
			drawRect(0, 0, SCRW, SCRH, getAlphaColor(0xff000000, game.screenT / T));
		}
	}
}

// 下楼
static void downFloor() {
	if (game.map) {
		mapDispose(game.map);
	}
	game.passed = false;
	game.passedT = 0;
	game.userControll = true;
	game.nextScreen = Screen_Game;
	game.floor--;
	game.mainRole->hp = game.mainRole->hps;
	Map *map = game.map = mapCreate();
	Room *initRoom = map->currentRoom;
	FloorRole *enemies = (FloorRole *)(void *)&floor_enemies[-game.floor - 1];
	// 添加主角。
	roomAddRole(initRoom, game.mainRole, 150, 150);
	// 添加怪物
	for (int i = 0; i < 30; i++) {
		FloorRole *fr = &enemies[i];
		if (fr->type == RoleType_Unknown) {
			break;
		}
		Room *room = map->roomList[fr->roomIndex];
		roomAddRole(room, roleCreate(fr->type, true, true), fr->x, fr->y);
	}
}

// 开始游戏
static void startGame() {
	game.mainRole = roleCreate(RoleType_LongXin, false, true);
	game.floor = 0;
	game.fail = false;
	game.failT = 0;
	downFloor();
}

// 结束游戏
static void endGame() {
	game.nextScreen = Screen_Init;
}

//////////////////////////////// 主菜单界面 ////////////////////////////

double at = 0;
static void initScreenUpdate(double t) {
	cls(33, 33, 33);
	// logo
	int32 mainColor = 0xffaaaaaaa;
	drawText(init_screen_caption, 300, 150, mainColor, 80);
	drawRect(200, 250, 500, 3, mainColor);
	drawRect(530, 265, 100, 45, getShiningColor(0xff666666, 0xffffffff, at += t, 1.5));
	drawText(init_screen_text1, 550, 270, 0xff000000, 30);
	// 按钮
	// drawRect(SCRW - 330, SCRH - 230, 30 * 6, 90, 0xff999999);
	// drawRect(SCRW - 330, SCRH - 130, 30 * 6, 90, 0xff555555);
	drawText(init_screen_exit, SCRW - 300, SCRH - 100, 0xffe0e0e0, 30);
	drawText(init_screen_start, SCRW - 300, SCRH - 200, 0xffe0e0e0, 30);
	drawText(init_screen_author, SCRW - 300, SCRH - 300, 0xff888888, 25);
}

static void initScreenEvent(int type, int p, int q) {
	if (isPointCollRect(p, q, SCRW - 330, SCRH - 230, 30 * 6, 90)) {
		game.nextScreen = Screen_Down;
	} else if (isPointCollRect(p, q, SCRW - 330, SCRH - 130, 30 * 6, 90)) {
		exit();
	}
}

//////////////////////////////// 下楼界面 //////////////////////////////

static void downScreenUpdate(double t) {
	cls(33, 33, 33);
	if (game.downT < 0.8) {
		game.downT += t;
		drawTextC(down_screen_ing, 0, 0, SCRW, SCRH, 234, 234, 234, 40);
	} else {
		// // Test 试玩版
		// if (game.floor == -1) {
		// 	drawTextC(passed_test_floor1, 0, 0, SCRW, SCRH, 234, 234, 234, 40);
		// 	return;
		// }
		game.downT = 0;
		game.nextScreen = Screen_Game;
		if (game.floor == 0) {
			startGame();
		} else {
			downFloor();
		}
	}
}

//////////////////////////////// 游戏界面 //////////////////////////////

static void gameUserControll(double t) {
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
		double angle = 0;
		if (apad->dragged) {  // 摇杆攻击
			angle = apad->angle;
		} else if (cloestEnemy) {  // 自动瞄准
			float ex = cloestEnemy->x;
			float ey = cloestEnemy->y;
			int preAttack = 1;	// 默认开启预瞄
			if (preAttack) {
				if (cloestEnemy->moving && fabs(cloestEnemy->v) < 300 && cloestEnemy->v < cloestEnemy->v0 * 2) {
					double t = getLineSize(role->x, role->y, ex, ey) / role->boll->data->v;
					ex += cloestEnemy->vx * t;
					ey += cloestEnemy->vy * t;
				}
			}
			angle = getAngle(role->x, role->y, ex, ey);
		} else {
			angle = role->faceAngle;
		}
		roleAttack(role, angle);
	} else {
		roleStopAttack(role);
	}
}

static void gameScreenEvent(int type, int p, int q) {
	int result = false;
	if (!result && game.userControll) {
		result |= cirpadEvent(game.dpad, type, p, q);
		result |= cirpadEvent(game.apad, type, p, q);
	}
	if (!result) {
		mapEvent(game.map, type, p, q);
	}
}

static void gameScreenUpdate(double t) {
	cls(33, 33, 33);

	// 逻辑
	mapUpdate(game.map, t);
	if (game.userControll) {
		gameUserControll(t);
	}

	// 绘图
	mapDraw(game.map, t);

	// UI
	if (game.userControll) {
		cirpadDraw(game.dpad, t);
		cirpadDraw(game.apad, t);
	}
	mapDrawUI(game.map, t);
}

//////////////////////////////// 通关界面 //////////////////////////////

static void passedScreenUpdate(double t) {
	RoleData *data = &role_longxin;
	cls(0, 0, 0);
	switch (game.passedScreenType) {
	case PassedScreen_None:
		game.passedRoleX = SCRW * 0.5;
		game.passedRoleY = SCRH * 0.7;
		game.passedRoleFz = data->r * 2 > 20 / 0.5 ? data->r * 2 > 70 / 0.5 ? 70 : data->r * 2 * 0.5 : 20;
		game.passedRoleT = 0;
		game.passedRoleRun = false;
		game.passedRoleFly = false;
		game.passedScreenType = PassedScreen_Story;
		game.passedEnd = false;
		game.passedTextT = 0;
		game.passedTextIndex = -1;
		break;
	case PassedScreen_Story:
		// 第一幕 传承
		if (game.passedTextIndex < 2) {
			if (game.passedTextIndex == -1) {  // 准备屏
				if (game.passedTextT < 0.5) {
					game.passedTextT += t;
				} else {
					game.passedTextIndex++;
					game.passedTextT = 0;
					game.passedRoleRun = true;
				}
			} else if (game.passedTextT < 2) {
				game.passedTextT += t;
				drawTextC(passed_screen_story[game.passedTextIndex], 0, SCRH * 0.7, SCRW, SCRH * 0.3, 179, 229, 252, 40);
			} else {
				game.passedTextIndex++;
				game.passedTextT = 0;
			}
		} else {
			game.passedScreenType = PassedScreen_Fly;
			game.passedTextIndex = 0;
			game.passedTextT = 0;
		}
		break;
	case PassedScreen_Fly:
		// 第二幕 飞行
		if (game.passedTextIndex < 3) {
			if (game.passedTextT < 2) {
				game.passedTextT += t;
				drawTextC(passed_screen_fly[game.passedTextIndex], 0, SCRH * 0.7, SCRW, SCRH * 0.3, 235, 235, 235, 40);
			} else {
				game.passedTextIndex++;
				game.passedTextT = 0;
				if (game.passedTextIndex == 1) {
					game.passedRoleFly = true;
				}
			}
		} else {
			game.passedScreenType = PassedScreen_Thanks;
			game.passedTextIndex = 0;
			game.passedTextT = 0;
			game.passedEnd = true;
		}
		break;
	case PassedScreen_Thanks:
		// 第三幕 鸣谢
		game.passedTextT += t;
		drawTextC(passed_screen_thanks, 0, 0, SCRW - 50, 200, 235, 235, 235, 50);
		for (int i = 0; i < 3; i++) {
			drawText(passed_screen_info[i], SCRW / 2 - 300, 200 + i * 100, 0xffcccccc, 30);
		}
		for (int i = 0; i < 5; i++) {
			drawText(passed_screen_ps[i], SCRW / 2 + 50, 200 + i * 50, 0xffcccccc, 30);
		}
		break;
	default:
		break;
	}
	if (game.passedEnd) {
		if (game.passedTextT > 3) {
			uint8 c = getShiningColor(0xff000000, 0xffffffff, game.passedTextT - 1, 1) % 256;
			drawTextC(passed_screen_back, 0, SCRH - 200, SCRW - 50, 200, c, c, c, 40);
		}
	} else {
		double upA = 2;
		if (game.passedRoleRun && game.passedRoleT < upA) {
			game.passedRoleT += t;
			game.passedRoleY = SCRH * 0.7 + game.passedRoleT * (game.passedRoleT - 2 * upA) * 0.4 * SCRH / upA / upA;
		} else if (game.passedRoleFly) {
			game.passedRoleY -= 100 * t;
		}
		drawCir(game.passedRoleX, game.passedRoleY, data->r + 100, 0x11ffffff);
		drawCir(game.passedRoleX, game.passedRoleY, data->r + 10, 0x11ffffff);
		drawCir(game.passedRoleX, game.passedRoleY, data->r + 3, data->color);
		drawCir(game.passedRoleX, game.passedRoleY, data->r, data->innerColor);
		drawCir(game.passedRoleX, game.passedRoleY, data->r + 3, 0x44000000);
		drawText(data->caption, game.passedRoleX - game.passedRoleFz / 2, game.passedRoleY - game.passedRoleFz / 2 - game.passedRoleFz / 8, 0xffE1E1F5, game.passedRoleFz);
	}
}

static void passedScreenEvent(int type, int p, int q) {
	if (game.passedEnd && game.passedTextT > 4) {
		if (type == MS_DOWN) {
			endGame();
		}
	}
}

//////////////////////////////// 游戏场景控制 //////////////////////////////

// static void gameDrawFPS(double t) {
// 	char s[50];
// 	game.fpsDT += t;
// 	if (game.fps < 1 || game.fpsDT > 1) {
// 		game.fpsDT = 0;
// 		game.fps = 1.0 / t;
// 	}
// 	sprintf(s, "FPS %d", (int)game.fps, SCRW, SCRH);
// 	drawTextC(s, 0, 0, SCRW, 60, 255, 255, 255, 30);
// }

void gameUpdate(long data) {
	int32 now = getuptime();
	double t = (now - game.drawLastTime) / 1000.0;
	game.drawLastTime = now;

	switch (game.screen) {
	case Screen_Init:
		initScreenUpdate(t);
		break;
	case Screen_Down:
		downScreenUpdate(t);
		break;
	case Screen_Game:
		gameScreenUpdate(t);
		break;
	case Screen_Passed:
		passedScreenUpdate(t);
		break;
	default:
		break;
	}
	screenGotoNextUpdate(t);

	// gameDrawFPS(t);
	ref(0, 0, SCRW, SCRH);
}

void gameEvent(int type, int p, int q) {
	if (game.nextScreen != Screen_None) {
		return;	 // 过度页面，无法进行任何操作。
	}
	switch (game.screen) {
	case Screen_Init:
		initScreenEvent(type, p, q);
		break;
	case Screen_Game:
		gameScreenEvent(type, p, q);
		break;
	case Screen_Passed:
		passedScreenEvent(type, p, q);
		break;
	default:
		break;
	}
	if (KY_UP == type && p == _BACK) {	// 返回键
		if (game.screen == Screen_Init) {
			exit();
		} else {
			dlgcreate(game_screen_exit_caption, game_screen_exit_info, 1);
		}
	}
	if (type == MR_DIALOG && p == 0) {	// 确定返回。
		endGame();
	}
}

void gameInit() {
	memset(&game, 0, sizeof(Game));
	game.screen = Screen_Init;

	if (SCRW > SCRH) {	// 横屏
		setscrsize(STAGEH * SCRW / SCRH, STAGEH);
	} else {  // 竖屏
		setscrsize(STAGEH, STAGEH * SCRH / SCRW);
	}
	game.dpad = cirpadCreate(200, SCRH - 200, 120, 40, false);
	game.apad = cirpadCreate(SCRW - 200, SCRH - 200, 120, 40, true);
	game.drawTimer = timercreate();
	timerstart(game.drawTimer, 1000 / FPS, 0, gameUpdate, 1);
	game.drawLastTime = getuptime();
}

void gameDispose() {
	timerstop(game.drawTimer);
	endGame();
	cirpadDispose(game.dpad);
	cirpadDispose(game.apad);
	printf(utf8_c("内存释放情况：%d/%d\n"), dispose_times, create_times);
}
