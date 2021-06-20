#ifndef _MAP_H_
#define _MAP_H_

#ifdef CAPP
#include "base.h"
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#include "global.h"
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
} Map;

void mapPrint(Map *map) {
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (int y = 0; y < 10; y++) {
		printf("%d ", y);
		for (int x = 0; x < 10; x++) {
			Room *room = map->rooms[y][x];
			if (room == NULL) {
				printf("  ");
			} else {
				printf("%s", room->caption);
			}
		}
		printf("\n");
	}
}

Map *mapInit(int luck) {
	// 初始化变量
	Map *map = malloc(sizeof(Map));
	map->roomCount = 0;
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			map->rooms[y][x] = 0;
		}
	}

	// 创建主房间
	int roomX = 1, roomY = 1;
	int downOrRight = rand() % 2;
	int turnIndex = rand() % 5;
	map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomInit(roomX, roomY, Room_Init);
	for (int i = 0; i < 6; i++) {
		if (i == turnIndex) {
			downOrRight = downOrRight == true ? false : true;
		}
		downOrRight ? roomY++ : roomX++;
		map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomInit(roomX, roomY, i == 5 ? Room_Boss : i == 4 ? Room_Shop
																														: Room_Battle);
	}

	// 查找次级房间的位置。
	int slots[100];
	int slotsSuper[100];
	int slotCount = 0;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int type = room->type;
		if (type == Room_Boss || type == Room_Shop) {
			continue;  // 终点的boss房间和商店房间，不连接次级房间。
		}
		int x = room->x;
		int y = room->y;
		slotsSuper[i] = x + y * 10;
		if (y > 0) {
			Room *top = map->rooms[y - 1][x];
			if (top == NULL) {
				slots[slotCount++] = x + (y - 1) * 10;
				// map->rooms[y - 1][x] = roomInit(x, y - 1, Room_Init);
			}
		}
		if (x < 9) {
			Room *right = map->rooms[y][x + 1];
			if (right == NULL) {
				slots[slotCount++] = x + 1 + y * 10;
				// map->rooms[y][x + 1] = roomInit(x + 1, y, Room_Init);
			}
		}
		if (y < 9) {
			Room *bottom = map->rooms[y + 1][x];
			if (bottom == NULL) {
				slots[slotCount++] = x + (y + 1) * 10;
				// map->rooms[y + 1][x] = roomInit(x, y + 1, Room_Init);
			}
		}
		if (x > 0) {
			Room *left = map->rooms[y][x - 1];
			if (left == NULL) {
				slots[slotCount++] = x - 1 + y * 10;
				// map->rooms[y][x - 1] = roomInit(x - 1, y, Room_Init);
			}
		}
	}
	for (int i = 0; i < slotCount; i++) {
		int index = rand() % slotCount;
		int tmp = slots[i];
		slots[i] = slots[index];
		slots[index] = tmp;
	}

	// 计算次级房间生成概率比。
	int ratioRanges[5];
	int ratioSum = 0;
	// printf("概率比：");
	for (int i = 0; i < 5; i++) {
		int room_luck = room_gene_data[i].luck;
		if (room_luck >= 0) {
			ratioRanges[i] = luck - room_luck;
		} else {
			ratioRanges[i] = -room_luck;
		}
		if (ratioRanges[i] <= 4) {
			ratioRanges[i] = 4;	 // 最低概率比
		}
		ratioSum += ratioRanges[i];
		// printf("%d ", ratioRanges[i]);
	}
	// printf("\n");
	// printf("总共：%d\n", ratioSum);
	// mapPrint(map);

	// 生成次级房间。
	float remainRoomCount = 4;
	for (int i = 0; i < slotCount; i++) {
		if (remainRoomCount <= 0) {
			break;	// 次级房间数量已足够。
		}
		int x = slots[i] % 10;
		int y = slots[i] / 10;
		int ratioRand = rand() % ratioSum;
		int ratioStart = 0;
		int roomGeneIndex = -1;
		for (int j = 0; j < 5; j++) {
			int range = ratioRanges[j];
			if (ratioRand >= ratioStart && ratioRand < ratioStart + range) {
				roomGeneIndex = j;
				break;
			}
			ratioStart += range;
		}
		if (roomGeneIndex > -1) {
			map->roomList[map->roomCount++] = map->rooms[y][x] = roomInit(roomX, roomY, room_gene_data[roomGeneIndex].type);
			remainRoomCount -= room_gene_data[roomGeneIndex].cost;
		}
	}

	// 初始化参数
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			Room *room = map->rooms[y][x];
			if (room != NULL) {
				room->x = x;
				room->y = y;
			}
		}
	}
	return map;
}

void mapDispose(Map *map) {
	free(map);
}

/**
 * 画小地图 
 */
void mapDraw(Map *map) {
}

#endif
