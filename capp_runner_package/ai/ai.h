#ifndef _AI_H_
#define _AI_H_

#include <base.h>

#include "../role.h"

/**
 * @brief 计算与最近敌人的夹角
 * 
 * @param role 当前角色
 * @param scatterAngle 附加一定随机散射的最大值，弧度制。
 */
float aiGetAngleToEnemy(struct _Role *role, float scatterAngle);

#endif