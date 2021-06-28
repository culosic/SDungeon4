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
#include "map.h"

// 房间图块类型
enum RoomTileType {
	RoomTile_Floor,	 // 地板
	RoomTile_Wall,	 // 墙体
	RoomTile_Door,	 // 门
};

// 房间图块，主要是墙壁和门
typedef struct _RoomTile {
	enum RoomTileType type;
	int x;
	int y;
	int w;
	int h;
	char *caption;
	struct _Room *linkRoom;
	int doorDirection;
} RoomTile;

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
	struct _Map *map;
	struct _Room *prevRoom;
	struct _Room *superRoom;
	struct _Room *linkRooms[4];
	int linkRoomCount;
	struct _RoomTile *tiles[10];
	int tileCount;

	int x;	//房间在地图上的位置
	int y;
	int w;	// 房间横向格子数
	int h;
	char *caption;		 // 房间大字标题
	enum RoomType type;	 // 房间类型
	int visible;		 // 房间是否已被发现

	float px;  // 房间x坐标
	float py;  // 房间y坐标
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
 * 初始化房间图块
 */
RoomTile *roomTileInit(int x, int y, int w, int h, enum RoomTileType type) {
	RoomTile *tile = malloc(sizeof(RoomTile));
	memset(tile, 0, sizeof(RoomTile));
	tile->x = x;
	tile->y = y;
	tile->w = w;
	tile->h = h;
	tile->type = type;
	return tile;
}

/**
 * 初始化房间
 * @param x 房间x坐标
 * @param y 房间y坐标
 * @param type 房间类型
 * @returns 房间对象
 */
Room *roomInit(struct _Map *map, int x, int y, enum RoomType type) {
	Room *room = malloc(sizeof(Room));
	memset(room, 0, sizeof(Room));
	room->map = map;
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
	float roomW = 500;	// 房间x宽度
	float roomH = 500;	// 房间y宽度
	room->px = (SCRW - roomW) / 2;
	room->py = (SCRH - roomH) / 2;
	return room;
}

/**
 * 释放房间占用内存
 */
void roomDispose(Room *room) {
	free(room);
}

/**
 * 初始化房间图块
 */
void roomInitTile(Room *room) {
	float roomW = 500;	// 房间x宽度
	float roomH = 500;	// 房间y宽度
	float wallD = 30;	// 墙壁厚度
	float doorW = 80;	// 门宽度
	// 地板
	RoomTile *floor = roomTileInit(wallD, wallD, roomW, roomH, RoomTile_Floor);
	floor->caption = room->caption;
	room->tiles[room->tileCount++] = floor;
	// 墙壁
	room->tiles[room->tileCount++] = roomTileInit(0, 0, roomW + wallD * 2, wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileInit(roomW + wallD, 0, wallD, roomH + wallD * 2, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileInit(0, roomH + wallD, roomW + wallD * 2, wallD, RoomTile_Wall);
	room->tiles[room->tileCount++] = roomTileInit(0, 0, wallD, roomH + wallD * 2, RoomTile_Wall);
	// 门
	for (int i = 0; i < room->linkRoomCount; i++) {
		Room *linkRoom = room->linkRooms[i];
		RoomTile *tile = NULL;
		if (room->x == linkRoom->x) {
			if (room->y > linkRoom->y) {  // 上
				tile = roomTileInit(wallD + roomW / 2 - doorW / 2, 0, doorW, wallD, RoomTile_Door);
				tile->doorDirection = 2;
			} else {  // 下
				tile = roomTileInit(wallD + roomW / 2 - doorW / 2, roomH + wallD, doorW, wallD, RoomTile_Door);
				tile->doorDirection = 8;
			}
		} else if (room->y == linkRoom->y) {
			if (room->x > linkRoom->x) {  // 左
				tile = roomTileInit(0, wallD + roomH / 2 - doorW / 2, wallD, doorW, RoomTile_Door);
				tile->doorDirection = 4;
			} else {  // 右
				tile = roomTileInit(roomW + wallD, wallD + roomH / 2 - doorW / 2, wallD, doorW, RoomTile_Door);
				tile->doorDirection = 6;
			}
		}
		tile->linkRoom = linkRoom;
		room->tiles[room->tileCount++] = tile;
	}
}

#endif