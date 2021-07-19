#ifndef _ROOM_H_
#define _ROOM_H_

#include <base.h>

#include "map.h"
#include "role.h"

// 房间图块类型
enum RoomTileType {
	RoomTile_Floor,		// 地板
	RoomTile_Wall,		// 墙体
	RoomTile_Door,		// 门
	RoomTile_Potions,		// 治疗草药
	RoomTile_Treasure,	// 宝箱
};

// 房间图块，主要是墙壁和门
typedef struct _RoomTile {
	enum RoomTileType type;
	int direction;
	int x;
	int y;
	int w;
	int h;
	struct _Room *linkRoom;
	int doorClosed;

	// 药房间治疗计时。
	double potionsT;
	double potionsUsed;
} RoomTile;

// 房间类型
enum RoomType {
	Room_Init,
	Room_Battle,
	Room_Potions,
	Room_Treasure,
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
	int passed;			 // 房间玩家是否已通过

	float px;	  // 房间x坐标
	float py;	  // 房间y坐标
	float roomW;  // 房间横宽
	float roomH;  // 房间纵宽
	float wallD;  // 墙壁厚度
	float doorW;  // 门宽度

	struct _Role *roles[100];  // 房间里的角色。
	int roleCount;
} Room;

RoomTile *roomTileCreate(int x, int y, int w, int h, enum RoomTileType type, int direction);
Room *roomCreate(struct _Map *map, int x, int y, enum RoomType type);
void roomDispose(Room *room);
void roomInitTile(Room *room);
void roomDraw(Room *room, double t);
void roomUpdate(Room *room, double t);

/**
 * @brief 向房间添加一个角色
 */
void roomAddRole(Room *room, struct _Role *role, float x, float y);
/**
 * @brief 跳转房间
 */
void roomRoleGoto(Room *room, struct _Role *role, Room *newRoom);
/**
 * @brief 地图碰撞检测
 * 
 * @return 碰撞到的地图图块，可以是门、地面等等。
 */
RoomTile *roomColl(Room *room, float x, float y, float r);
/**
 * @brief 检测是否碰撞到敌人
 */
struct _Role *roomCollEnemy(Room *room, float x, float y, float r, struct _Role *role);
/**
 * @brief 找到最近的敌人
 */
struct _Role *roomGetCloestEnemy(Room *room, struct _Role *role);

#endif