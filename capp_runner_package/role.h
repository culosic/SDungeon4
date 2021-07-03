#ifndef _ROLE_H_
#define _ROLE_H_

#include "boll.h"
#include "room.h"

// 角色数据定义
typedef struct _Role {
	Room *room;
	float x;
	float y;
	float v0;
	double vx;		   // 当前x速度
	double vy;		   // 当前y速度
	double faceAngle;  // 面向

	int moving;		 // 是否正在主动移动
	int attacking;	 // 是否正在攻击
	double attackingT;	 // 攻击准备计时

	Boll *boll;	 // 子弹链表
} Role;

/**
 * 创建一个角色
 */
Role *roleCreate(Room *room, int x, int y);
/**
 * 释放角色占用内存
 */
void roleDispose(Role *role);
/**
 * 更新角色
 */
void roleUpdate(Role *role, float t);
/**
 * 绘制角色
 */
void roleDraw(Role *role);

void roleMove(Role *role, double angle);
void roleStopMove(Role *role);
void roleAttack(Role *role, double angle);
void roleStopAttack(Role *role);

#endif