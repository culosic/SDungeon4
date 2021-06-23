#ifndef _ROOM_H_
#define _ROOM_H_

#ifdef CAPP
#include "base.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "global.h"

// 房间类型
enum RoomType {
	Room_Init,
	Room_Trap,
	Room_Battle,
	Room_Potions,
	Room_Treasure,
	Room_Elite,
	Room_Shop,
	Room_Boss,
};

// 次级房间随机生成数据
typedef struct _RoomGenerateData {
	enum RoomType type;
	int luck;
	float cost;	 // 次级房间消耗游戏时间比率，用来控制游戏时长，和遵守玩家耐心
} RoomGenerateData;

// 房间数据定义
typedef struct _Room {
	struct _Room *prevRoom;
	struct _Room *superRoom;
	struct _Room *linkRooms[4];
	int linkRoomCount;
	int x;	//房间在地图上的位置
	int y;
	int w;	// 房间横向格子数
	int h;
	char *caption;		 // 房间大字标题
	enum RoomType type;	 // 房间类型
	int visible;		 // 房间是否已被发现
} Room;

// 次级房间随机生成数据
struct _RoomGenerateData room_gene_data[5] = {
	{Room_Trap, -20, 0.8},
	{Room_Battle, 10, 1},
	{Room_Potions, 10, 0.6},
	{Room_Treasure, 20, 0.8},
	{Room_Elite, 40, 1.5},
};

/**
 * 初始化房间
 * @param x 房间x坐标
 * @param y 房间y坐标
 * @param type 房间类型
 * @returns 房间对象
 */
Room *roomInit(int x, int y, enum RoomType type) {
	Room *room = malloc(sizeof(Room));
	memset(room, 0, sizeof(Room));
	room->x = x;
	room->y = y;
	room->w = 10;
	room->h = 10;
	room->type = type;
	switch (type) {
	case Room_Init:
		room->caption = utf8_c("初");
		break;
	case Room_Battle:
		room->caption = utf8_c("战");
		break;
	case Room_Trap:
		room->caption = utf8_c("阵");
		break;
	case Room_Potions:
		room->caption = utf8_c("釜");
		break;
	case Room_Treasure:
		room->caption = utf8_c("箱");
		break;
	case Room_Elite:
		room->caption = utf8_c("魂");
		break;
	case Room_Shop:
		room->caption = utf8_c("店");
		break;
	case Room_Boss:
		room->caption = utf8_c("狱");
		break;
	default:
		room->caption = utf8_c("");
		break;
	}
	return room;
}

/**
 * 释放房间占用内存
 */
void roomDispose(Room *room) {
	free(room);
}

#endif