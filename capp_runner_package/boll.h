#ifndef _BOLL_H_
#define _BOLL_H_

#include "room.h"

// 存放子弹信息，以及发射的子弹
typedef struct _BollData {
	struct _Room *room;	 // 所在房间

	float r;		   // 大小
	int32 color;	   // 颜色
	double v;		   // 发射初速度
	float range;	   // 射程
	float scattering;  // 散射
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

Boll *bollCreates(struct _Room *room, float r, int32 color, double v, float range);
void bollDispose(Boll *head);
void bollUpdate(Boll *head, double t);
void bollDraw(Boll *head);

/**
 * @brief 发射一个子弹
 * 
 * @param head 
 * @param x 
 * @param y 
 * @param angle 
 */
void bollAdd(Boll *head, float x, float y, double angle);

#endif