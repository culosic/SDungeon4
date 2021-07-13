#ifndef _ROLE_H_
#define _ROLE_H_

#include <base.h>

#include "boll.h"
#include "room.h"

// 血量扣除动画的速度。每秒钟扣除血量的比例。
float hp_decrease_animation_v = 5;

// 角色枚举表
enum RoleType {
	RoleType_Unknown,

	// 人物角色
	RoleType_LongXin = 0x000001,	// 龙辛
	RoleType_JingYu = 0x000002,		// 惊羽
	RoleType_Wu_JingYu = 0x000003,	// 舞·静雨
	RoleType_Ne_Giles = 0x000004,	// 烈贾尔斯
	RoleType_Clark = 0x000005,		// 克拉克

	// 第一层小怪
	RoleType_Mouse = 0x010001,
	RoleType_Wolf = 0x010002,
	RoleType_Scorpion = 0x010003,

	// 第一层boss
	RoleType_Ghost = 0x01ff01,
};

typedef struct _RoleData {
	// 人物标识
	char *name;		 // 姓名
	char *caption;	 // 地图大字
	char *info;		 // 人物描述
	int r;			 // 地图人物半径
	int color;		 // 地图人物颜色
	int innerColor;	 // 地图人物内部颜色
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
	enum RoleType type;		 // 角色类型

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
	double v;			 // 当前总速度
	double vx;			 // 当前x速度
	double vy;			 // 当前y速度
	double faceAngle;	 // 面向
	int moving;			 // 是否正在主动移动
	int attacking;		 // 是否正在攻击
	double attackingT;	 // 攻击准备计时
	struct _Boll *boll;	 // 子弹链表

	// 绘制、动画相关
	int fw;				// 角色在地图标题字体大小
	float hpPercentT;	// 血量扣除动画计时。
	float dyingAlphaT;	// 死亡渐隐动画计时。

	// AI
	void *ai;  // ai对象指针
} Role;

Role *roleCreate(enum RoleType type, int enemy, int ai);
void roleDispose(Role *role);
void roleUpdate(Role *role, double t);
void roleUpdateAddition(Role *role, double t);
void roleDraw(Role *role, double t);

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