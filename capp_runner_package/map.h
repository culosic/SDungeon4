#ifndef _MAP_H_
#define _MAP_H_

#include "room.h"

/**
 * 
 * 地图：10 * 10
 * 
 * * 商店
 * 
 * [] 0 1 2 3 4 5 * b []
 * 
 * 0 1 2 3 4 5
 *  		 *
 * 			 b
 * 
 * 0 1 2 3 4
 *         5
 * 		   *
 * 		   b
 * 
 * 目标：让游戏 结构从简、清晰、但是仍有挑战性
 * 
 * 
 * 房间
 * 
 * * 主房间：距离boss总是5个房间，这5个房间可以是拐点，或者不拐，最后一个房间是商店。也就是说有4个主战斗房间
 * * 分支房间：从主房间、战斗房间上分支出去的房间
 * * * 分支房间排列：如果主房间是横向，那么分支纵向生成；反之则横向生成；同理拐点也是向除了拐前和拐后之外的方向生成
 * * * 分支房间个数：普通人运气值总共Q0 = 60，总共<5个房间，是一下房间的加权值：
 * * * * 		房间\Q0				60		0		100
 * * * * -20陷阱房间(比重1)			20		20		20
 * * * * 0战斗房间(比重0.5)			60		4		100
 * * * * 20药水房间(比重0.5)		40		4		80
 * * * * 50宝物房间(比重1.5)		10		4		50
 * * * * 50小boss房间（比重1.5)		10		4		50
 * * * 按剩余运气进行随机，随机的概率比为(Q0 - x房间消耗运气)
 * * * 如果房间消耗为负数，那么直接=房间消耗汽运绝对值
 * * * 规定运气极低情况为5:1，如果概率比为负数，那么直接=最大陷阱房间消耗气运绝对值 * 20%
 */

// 地图数据定义
typedef struct _Map {
	struct _Room *rooms[10][10];  // 房间的指针数组
	struct _Room *roomList[100];  // 房间的指针数组
	int roomCount;				  // 房间数
	struct _Room *currentRoom;	  // 当前所在房间
} Map;

Map *mapCreate(int luck);
void mapDispose(Map *map);
void mapDraw(Map *map, double t);
void mapUpdate(Map *map, double t);

/**
 * @brief 画小地图
 */
void mapDrawMiniMap(Map *map, double t);

#endif