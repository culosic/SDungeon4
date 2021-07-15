#ifndef _DATA_H_
#define _DATA_H_

#include <base.h>

#include "role.h"
#include "room.h"

////////////////// 地图数据 /////////////////////////

char *room_init_caption = "初";
char *room_battle_caption = "战";
char *room_potions_caption = "药";
char *room_treasure_caption = "箱";
char *room_boss_caption = "狱";

enum RoomType room_gene_data_static[2] = {
	Room_Potions,
	Room_Treasure,
};

////////////////// 玩家人物属性相关 ////////////////////////

struct _RoleData role_longxin = {
	"龙辛",
	"龙",
	"男，一个勇敢的探险家，四处冒险，写下了很多故事。但是如此诡秘的地牢，他还从来没有见过。虽然此处凶险，但也伴随机遇，他怎么可能放过呢？",
	30,
	0xff009688,
	0xff005737,

	100,// 10,
	2,
	300,
};

////////////////// 第一层怪物 ////////////////////////

struct _RoleData role_mouse = {
	"酸败鼠",
	"鼠",
	"地牢顶部楼层中随处可见的老鼠，靠吃腐肉为生，可以发射腐蚀性的毒液攻击目标。",
	20,
	0xff996b1f,
	0xff663300,

	6,
	1,
	150,
};

struct _RoleData role_wolf = {
	"柴狼",
	"狼",
	"敏捷、凶悍，一般来自森林，到此地牢寻找猎物，那些来探索地牢的人类和精灵是他的最爱",
	25,
	0xff666666,
	0xff333333,

	10,
	3,
	200,
};

struct _RoleData role_scorpion = {
	"大蝎",
	"蝎",
	"丛林中常见的妖兽，体型较大，可以发射毒液攻击猎物，作战能力较强。",
	35,
	0xff9966cc,
	0xff6633aa,

	15,
	3,
	100,
};

////////////////// 第一层boss ////////////////////////

struct _RoleData role_ghost = {
	"幽鬼",
	"鬼",
	"日积月累...不断吞噬...最后，它成为了一个怪物！一团巨大的恶鬼。恐怖、诡异的身影，成为了每个探索者的噩梦。",
	60,
	0xff444444,
	0xff000000,

	60,
	3,
	100,
};

struct _RoleData role_ghost_main = {
	"魂魄",
	"魄",
	"幽鬼头领",
	40,
	0xff444444,
	0xff000000,

	60,
	3,
	200,
};

struct _RoleData role_ghost_child = {
	"鬾鬼",
	"鬾",
	"幽鬼附属",
	20,
	0xff444444,
	0xff000000,

	4,
	1,
	300,
};

////////////////// 第二层怪物 ////////////////////////

struct _RoleData role_ant = {
	"酸蚀蚁",
	"蚁",
	"成群出没，靠口中分泌的强烈酸液捕食猎物。",
	12,
	0xff332200,
	0xff332200,

	8,
	2,
	100,
};

struct _RoleData role_frog = {
	"毒蛙",
	"蛙",
	"毒性较强，同时擅长跃击。",
	25,
	0xff22aa37,
	0xff008837,

	20,
	8,
	150,
};

struct _RoleData role_snake = {
	"毒蛇",
	"蛇",
	"毒液有剧毒，喷射毒液杀死猎物后吞掉猎物。",
	20,
	0xff800000,
	0xff610000,

	12,
	5,
	0,
};

////////////////// 第二层boss ////////////////////////

struct _RoleData role_flamem = {
	"炎兽",
	"炎",
	"元素精灵，可以聚集周围的火元素，胆敢靠近者会被慢慢烧成灰烬。",
	70,
	0xffff7700,
	0xff663300,

	220,
	3,
	100,
};

////////////////// 第三层怪物 ////////////////////////

struct _RoleData role_bee = {
	"杀人蜂",
	"蜂",
	"成群出没，具有强烈的毒性，牙齿可以咬穿皮革。",
	20,
	0xffffaa1f,
	0xffaa8800,

	10,
	8,
	150,
};

struct _RoleData role_tiger = {
	"虎拳",
	"虎",
	"高阶妖兽，半人半虎，擅长拳击。",
	30,
	0xffffffff,
	0xff999999,

	30,
	16,
	200,
};

struct _RoleData role_tortoise = {
	"玄龟",
	"龟",
	"高阶妖兽，龟甲坚硬无比",
	60,
	0xff99aacc,
	0xff607d8b,

	100,
	0,
	50,
};

////////////////// 第三层boss ////////////////////////

struct _RoleData role_edragon = {
	"纯阴·地龙",
	"阴",
	"龙族的一员，日夜守在传承附近，可是怎么也得不到传承。",
	80,
	0xff000000,
	0xff000000,

	300,
	4,
	200,
};

#endif