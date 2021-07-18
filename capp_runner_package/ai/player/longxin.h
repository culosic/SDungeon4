#ifndef _AI_LONGXIN_H_
#define _AI_LONGXIN_H_

#include <base.h>

#include "../../role.h"

// 鼠的实时ai数据
typedef struct _AILongxin {
	struct _Role *role;
} AILongxin;

AILongxin *aiLongxinCreate(struct _Role *role);
void aiLongxinDispose(AILongxin *ai);
void aiLongxinUpdate(AILongxin *ai, double t);

#endif