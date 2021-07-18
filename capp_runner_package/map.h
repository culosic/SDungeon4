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
} Map;

Map *mapCreate();
void mapDispose(Map *map);
void mapDraw(Map *map, double t);
void mapUpdate(Map *map, double t);

/**
 * @brief 画小地图
 */
void mapDrawMiniMap(Map *map, double t);

/**
 * @brief 地图是否通过、过关
 */
int mapIsPassed(Map *map);


#endif