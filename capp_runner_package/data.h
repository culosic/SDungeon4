#ifndef _DATA_H_
#define _DATA_H_

#include "role.h"
#include "room.h"

////////////////// 地图数据 /////////////////////////

char *room_init_caption = "初";
char *room_battle_caption = "战";
char *room_trap_caption = "阵";
char *room_potions_caption = "釜";
char *room_treasure_caption = "箱";
char *room_elite_caption = "魂";
char *room_shop_caption = "店";
char *room_boss_caption = "狱";

struct _RoomGenerateData room_gene_data[5] = {
	{Room_Trap, -20, 0.8},
	{Room_Battle, 10, 1},
	{Room_Potions, 10, 0.6},
	{Room_Treasure, 20, 0.8},
	{Room_Elite, 40, 1.5},
};

////////////////// 玩家人物属性相关 ////////////////////////

struct _RoleData role_longxin = {
	"龙辛",
	"龙",
	"男，一个勇敢的探险家，四处冒险，写下了很多故事。但是如此诡秘的地牢，他还从来没有见过。虽然此处凶险，但也伴随机遇，他怎么可能放过呢？",
	30,
	0xff009688,
	0xff005737,

	10,
	10,
	2,
	300,
	10,

	10,
	2,
	1,
};

struct _RoleData role_jingyu = {
	"惊羽",
	"羽",
	"一个身着奇装异服的小伙子，他看起来并不来自这个世界。但是他有必须来这里的原因，那就是————变强！他说过，压迫的力量越强，反抗就会更加猛烈！",
	30,
	0xff009688,
	0xff009688,

	6,
	2,
	3,
	350,
	10,

	10,
	4,
	1,
};

struct _RoleData role_wu_jingyu = {
	"舞·静雨",
	"雨",
	"精灵少女，银发、皮肤白皙。擅长光魔法。由于一些原因，她和名字同音的好友惊羽一起踏上了征程，一路上经历了很多，即时她遇到了难以摆平的困难，也不会放弃同伴和自己。",
	20,
	0xff009688,
	0xff009688,

	12,
	12,
	1,
	250,
	10,

	10,
	1.5,
	1,
};

struct _RoleData role_ne_giles = {
	"烈贾尔斯",
	"贾",
	"烈族之人。精通枪械。长辈们把他逼到了绝境，于是他跑出了部落，流亡在外国他乡。前方或许没有路，但是他也一路走着。他觉得一定有什么东西在等待着他，那个东西在“发光”，光芒是如此令人向往。",
	40,
	0xff009688,
	0xff009688,

	6,
	1,
	3,
	300,
	10,

	10,
	2,
	1.5,
};

struct _RoleData role_clark = {
	"克拉克",
	"克",
	"男精灵。掌握雷电魔法。他脾气火爆、作恶多端。或许只因旁人说了一句他不满意的话，他也要大打出手。",
	20,
	0xff009688,
	0xff009688,

	12,
	8,
	2,
	400,
	10,

	10,
	3,
	1,
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
	0,
	1,
	200,
	10,

	0,
	0,
	0,
};

struct _RoleData role_wolf = {
	"柴狼",
	"狼",
	"敏捷、凶悍，一般来自森林，到此地牢寻找猎物，特别是来探索地牢的、可口的人类和精灵",
	25,
	0xff666666,
	0xff333333,

	8,
	0,
	3,
	400,
	10,

	0,
	0,
	0,
};

struct _RoleData role_scorpion = {
	"大蝎",
	"蝎",
	"丛林中常见的妖兽，体型较大，可以发射毒液攻击猎物，作战能力较强。",
	35,
	0xff9966cc,
	0xff6633aa,

	15,
	0,
	3,
	250,
	10,

	0,
	0,
	0,
};

struct _RoleData role_ghost = {
	"幽鬼",
	"鬼",
	"日积月累...不断吞噬...最后，它成为了一个怪物！一团巨大的恶鬼。是消灭它，还是和它融为一体，全靠本事了。",
	60,
	0xff444444,
	0xff000000,

	60,
	0,
	8,
	250,
	10,

	0,
	0,
	0,
};

#endif