#ifndef _ROLE_H_
#define _ROLE_H_

#ifdef CAPP
#include "base.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "global.h"

// 角色数据定义
typedef struct _Role {
	float x;
	float y;
	float v0;
	float a;   // 开始行走和结束行走的实时加速度
	float vx;  // 当前x轴速度分量
	float vy;  // 当前y轴速度分量
} Role;

/**
 * 初始化
 */
Role *roleInit(int x, int y) {
	Role *role = malloc(sizeof(Role));
	memset(role, 0, sizeof(Role));
	role->x = x;
	role->y = y;
	role->v0 = 1;
	return role;
}

/**
 * 释放角色占用内存
 */
void roleDispose(Role *role) {
	free(role);
}

/**
 * 更新角色
 */
void roleUpdate(Role *role) {
	role->x += role->vx;
	role->y += role->vy;
}

/**
 * 角色控制事件
 */
void roleEvent(Role *role, int type, int p, int q) {
	if (type == KY_DOWN) {
		switch (p) {
		case _UP:
			role->vx = 0;
			role->vy = -role->v0;
			break;
		case _RIGHT:
			role->vx = role->v0;
			role->vy = 0;
			break;
		case _DOWN:
			role->vx = 0;
			role->vy = role->v0;
			break;
		case _LEFT:
			role->vx = -role->v0;
			role->vy = 0;
			break;
		default:
			break;
		}
	} else if (type == KY_UP) {
		switch (p) {
		case _UP:
		case _RIGHT:
		case _DOWN:
		case _LEFT:
			role->vx = 0;
			role->vy = 0;
			break;
		default:
			break;
		}
	}
}

#endif