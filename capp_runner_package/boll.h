#ifndef _BOLL_H_
#define _BOLL_H_

#include "base.h"
#include "role.h"
#include "room.h"

// 存放子弹信息。
typedef struct _BollData {
	float r;		   // 大小
	int32 color;	   // 颜色
	double v;		   // 发射初速度
	float range;	   // 射程
	float scattering;  // 散射
} BollData;

// 子弹节点
typedef struct _Boll {
	struct _Room *room;	 // 所在房间
	struct _Role *role;	 // 发射者
	float x;
	float y;
	double vx;	// 当前x速度
	double vy;	// 当前y速度

	struct _BollData *data;	 // 子弹信息
	struct _Boll *next;		 // 记录下一个子弹，形成链表
} Boll;

Boll *bollsCreate(float r, int32 color, double v, float range);
void bollsDispose(Boll *head);
void bollUpdate(Boll *head, double t);
void bollDraw(Boll *head, double t);

/**
 * @brief 发射一个子弹
 * 
 * @param head 
 * @param room 子弹发射者所在的房间
 * @param x 发射的起始x位置
 * @param y 发射的起始y位置
 * @param angle 发射角度
 */
void bollAdd(Boll *head, struct _Role *role, float x, float y, double angle);

#endif