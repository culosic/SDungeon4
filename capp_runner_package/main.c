/*
S地牢

1. 实现地图
2. 实现人物行走
3. 基本ui
4. 攻击


2021年6月18日

*/

#define CAPP

#include "base.h"
#include "game.h"
#include "map_draw.h"

//入口函数，程序启动时开始执行
int init() {
	gameInit();
	return 0;
}

//event函数，接收消息事件
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

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause() {
	return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume() {
	return 0;
}

//应用退出函数，在应用退出时可做一些内存释放操作
int exitApp() {
	gameDispose();
	return 0;
}