/**
 * 程序名：S地牢0.4-传承
 * 说明：一个地牢探险游戏，经过层层闯关，最终目的是到达最深处，拿到被埋葬的圣人永炼-千刃的传承。相比0.3版本，地图生成比较简单，改战棋模式为即时战斗的弹幕游戏。
 * 作者：火烧云
 * 时间：2021年6月18日 到 2021年7月25日
 * 
 * QQ：2268881308
 * 游戏开发群：496717720
 * 手机CAPP大群：606757263
 * 
 * 这段时间在陆陆续续的做这个游戏，终于做好了，看到成品，起码自己玩的挺开心的嘻嘻。
 * 做游戏挺肝的哈哈，但是我特别喜欢做游戏。尽管现在水平还不够，但是我会尽我所能尝试、学习。如果太肝了，就简化一下设计。
 * 这个游戏基本开发完成了，当然实在简化设计的情况下。后面我暂时没有开发较大、耗时项目的计划了。
 * 我决定有闲暇时间就学画点像素画，毕竟现在没图片，光几何图像的游戏，还是太抽象了哈哈。
 */

#include <base.h>

#include "ai/ai.c"
#include "ai/floor1/ghost.c"
#include "ai/floor1/mouse.c"
#include "ai/floor1/scorpion.c"
#include "ai/floor1/wolf.c"
#include "ai/floor2/ant.c"
#include "ai/floor2/flamem.c"
#include "ai/floor2/frog.c"
#include "ai/floor2/snake.c"
#include "ai/floor3/bee.c"
#include "ai/floor3/edragon.c"
#include "ai/floor3/tiger.c"
#include "ai/floor3/tortoise.c"
#include "ai/player/longxin.c"
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
			// exit();
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