#ifndef _ROLE_H_
#define _ROLE_H_

#include "boll.h"
#include "room.h"

typedef struct _RoleData {
	// 人物标识
	char *name;	   // 姓名
	char *caption;  // 地图大字
	char *info;   // 人物描述
	int r;			   // 地图人物半径
	int color;		   // 地图人物颜色
	int innerColor;	   // 地图人物内部颜色
	// 战斗属性
	float hp;	// 基础生命值
	float mp;	// 基础蓝量
	float atk;	// 基础攻击力
	float v0;	// 基础移动速度
	float pow;	// 基础力量
	// 成长属性，实际效果 = level/5*level_hp
	float level_hp;	  // 成长生命
	float level_mp;	  // 成长蓝量
	float level_atk;  // 成长攻击
} RoleData;

// 角色数据定义
typedef struct _Role {
	struct _RoleData *data;	 // 角色数据
	int fw;			 // 角色在地图标题字体大小

	int enemy;
	float hps;
	float hp;
	float mps;
	float mp;
	float headEquip;	// 头部装备
	float bodyEquip;	// 上装
	float footEquip;	// 下装
	float extraEquip1;	// 配饰1
	float extraEquip2;	// 配饰2

	struct _Room *room;	 // 当前所在房间
	float x;
	float y;
	double vx;			// 当前x速度
	double vy;			// 当前y速度
	double faceAngle;	// 面向
	int moving;			// 是否正在主动移动
	int attacking;		// 是否正在攻击
	double attackingT;	// 攻击准备计时

	struct _Boll *boll;	 // 子弹链表
} Role;

Role *roleCreate(RoleData *data, struct _Room *room, int x, int y, int enemy);
void roleDispose(Role *role);
void roleUpdate(Role *role, float t);
void roleDraw(Role *role);

/**
 * @brief 角色开始移动
 * 
 * @param role 
 * @param angle 移动方向
 */
void roleMove(Role *role, double angle);
/**
 * @brief 角色停止移动
 * 
 * @param role 
 */
void roleStopMove(Role *role);
/**
 * @brief 角色开始攻击
 * 
 * @param role 
 * @param angle 攻击方向
 */
void roleAttack(Role *role, double angle);
/**
 * @brief 角色停止攻击
 * 
 * @param role 
 */
void roleStopAttack(Role *role);

#endif