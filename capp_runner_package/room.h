#ifndef _ROOM_H_
#define _ROOM_H_

#include "map.h"
#include "role.h"

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

	int x;				 // 房间在地图上的x位置
	int y;				 // 房间在地图上的y位置
	int w;				 // 房间横向格子数
	int h;				 // 房间纵向格子数
	enum RoomType type;	 // 房间类型
	char *caption;		 // 房间大字标题
	int visible;		 // 房间是否已被发现

	float px;  // 房间x坐标
	float py;  // 房间y坐标

	// Role *roles[100];  // 房间里的角色。
} Room;

RoomTile *roomTileCreate(int x, int y, int w, int h, enum RoomTileType type);
Room *roomCreate(struct _Map *map, int x, int y, enum RoomType type);
void roomDispose(Room *room);
void roomInitTile(Room *room);
void roomDraw(Room *room);

#endif