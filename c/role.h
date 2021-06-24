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

enum RoleState {
	RoleIdle,
	RoleRun,
	RoleAttack,
};

// 角色数据定义
typedef struct _Role {
	float x;
	float y;
	float v0;
	float vd;

	enum RoleState state;
} Role;

/**
 * 初始化
 */
Role *roleInit(int x, int y) {
	Role *role = malloc(sizeof(Role));
	memset(role, 0, sizeof(Role));
	role->x = x;
	role->y = y;
	role->state = RoleIdle;
	return role;
}

/**
 * 释放角色占用内存
 */
void roleDispose(Role *role) {
	free(role);
}

void roleUpdate() {
}

#endif