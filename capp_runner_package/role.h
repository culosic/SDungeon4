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
	int direction;	// 移动方向
	float v;		// 当前速度

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
/**
 * 角色控制事件
 */
void roleEvent(Role *role, int type, int p, int q);

#endif