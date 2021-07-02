#ifndef _BOLL_H_
#define _BOLL_H_

#include "room.h"

// 存放子弹信息，以及发射的子弹
typedef struct _BollData {
	Room *room;	 // 所在房间

	float r;		   // 大小
	int32 color;	   // 颜色
	double v;		   // 发射初速度
	float range;	   // 射程
	float scattering;  // 散射
					   // struct _Boll *next;	 // 记录下一个子弹，形成链表
} BollData;

// 子弹节点
typedef struct _Boll {
	float x;
	float y;
	double vx;	// 当前x速度
	double vy;	// 当前y速度

	struct _BollData *data;	 // 子弹信息
	struct _Boll *next;		 // 记录下一个子弹，形成链表
} Boll;

/**
 * 初始化子弹信息
 */
Boll *bollCreates(Room *room, float r, int32 color, double v, float range);
/**
 * 删除所有子弹
 */
void bollDispose(Boll *head);
/**
 * 发射一个子弹
 */
void bollAdd(Boll *head, float x, float y, float dx, float dy);
/**
 * 更新子弹
 */
void bollUpdate(Boll *head, double dt);
/**
 * 绘制子弹
 */
void bollDraw(Boll *head);

#endif