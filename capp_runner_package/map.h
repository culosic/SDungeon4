#ifndef _MAP_H_
#define _MAP_H_

#include <base.h>

#include "room.h"

// 地图数据定义
typedef struct _Map {
	struct _Room *rooms[10][10];  // 房间的指针数组
	struct _Room *roomList[100];  // 房间的指针数组
	int roomCount;				  // 房间数
	struct _Room *currentRoom;	  // 当前所在房间
	struct _Room *bossRoom;		  // boss房间

	struct _RoomTile *activeTile;

	// 弹窗继续文字闪烁计时
	double dialogContinueT;

	// 宝箱弹窗
	int boxSelect1;
	int boxSelect2;
	int boxSelectIndex;
	double boxOpenT;

	// boss演出
	int bossPreShow;
	double bossT;
} Map;

Map *mapCreate();
void mapDispose(Map *map);
void mapDraw(Map *map, double t);
void mapUpdate(Map *map, double t);
void mapEvent(Map *map, int type, int p, int q);

/**
 * @brief 画UI
 */
void mapDrawUI(Map *map, double t);

#endif