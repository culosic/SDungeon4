#ifndef _DATA_H_
#define _DATA_H_

#include <base.h>

#include "role.h"
#include "room.h"

/////////////////// 场景数据 ////////////////////////

char *init_screen_caption = "S地牢";
char *init_screen_text1 = "传承";
char *init_screen_author = "火烧云作品(v0.4.5)";
char *init_screen_start = "开始游戏";
char *init_screen_exit = "退出";

char *down_screen_ing = "下楼中...";

char *game_screen_exit_caption = "\x7e\xd3\x67\x5f\x0\x0";
char *game_screen_exit_info = "\x8f\xd4\x56\xde\x4e\x3b\x83\xdc\x53\x55\x4f\x1a\x4e\x22\x59\x31\x6e\x38\x62\xf\x8f\xdb\x5e\xa6\xff\xc\x78\x6e\x5b\x9a\x89\x81\x8f\xd4\x56\xde\x54\x17\xff\x1f\x0\x0";

char *passed_screen_story[10] = {
	"【你已经历考验、成为下一代传承者】",
	"【愿你能坚守本心】",
};

char *passed_screen_fly[10] = {
	"地牢已经坍塌，只能靠旁边一个很深的洞穴逃生",
	"不用担心，传承赋予了你飞行的能力",
	"试炼已经结束，去寻找属于自己的路吧",
};

char *passed_screen_thanks = "恭喜通关 感谢游玩";

char *passed_screen_info[10] = {
	"程序   火烧云",
	"美术   无",
	"音乐   无",
};

char *passed_screen_ps[10] = {
	"真的真的非常感谢你能玩到最后",
	"这个游戏虽然非常抽象",
	"也没有美术、音乐",
	"我耗费了许多精力",
	"但愿能给玩游戏的你带来一点点快乐",
};

char *passed_screen_back = "触摸屏幕返回主菜单";

////////////////// 界面、弹窗信息 /////////////////////////

char *headinfo_hp = "生命 %d/%d";
char *headinfo_others = "攻 %d 射速 %.1f 移速 %d";
char *mapinfo_caption = "图";

char *dialog_box_caption = "宝箱";
char *dialog_box_info = "你可以祈祷宝箱中符印的属性，点击宝箱来选择其中的一种：";
char *dialog_box_hp = "磐石";
char *dialog_box_hp_opened = "生命上限提升";
char *dialog_box_atk = "破坏";
char *dialog_box_atk_opened = "攻击力提升";
char *dialog_box_atkv = "急速";
char *dialog_box_atkv_opened = "攻击速度提升";
char *dialog_box_v = "轻灵";
char *dialog_box_v_opened = "移动速度提升";
char *dialog_box_ext = "无尽";
char *dialog_box_ext_opened = "弹幕数量增加";

char *dialog_loss_caption = "死亡";
char *dialog_loss_info = "在这阴暗的地牢中，你身受重伤，最终还是倒下了……";
char *dialog_loss_back = "触摸屏幕返回主菜单";

char *dialog_pass_caption = "胜利";
char *dialog_pass_info_levelup = "升级！你的生命、攻速、攻击提升";
char *dialog_pass_info_nextlevel_2 = "【下一层】会更加凶险，野兽密集";
char *dialog_pass_info_nextlevel_3 = "下面是【最后一层】，妖兽强大但稀少";
char *dialog_pass_info_allwin = "击败【最终的守层者】后";
char *dialog_pass_info_found = "你发现了传承遗址……";
char *dialog_pass_next = "触摸屏幕进入下一层";
char *dialog_pass_end = "触摸屏幕继续";

char *toast_heal = "治疗中";

char *boss_start = "触摸屏幕开始战斗";

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

typedef struct _FloorEnemy {
	int roomIndex;
	enum RoleType type;
	int x;
	int y;
} FloorRole;

// 所有楼层怪物数据
FloorRole floor_enemies[4][100] = {
	// 第一关。boss有两个形态
	{
		{1, RoleType_Mouse, 100, 100},
		{1, RoleType_Mouse, 600, 100},
		{1, RoleType_Mouse, 600, 400},
		{1, RoleType_Mouse, 100, 400},

		{2, RoleType_Mouse, 300, 200},
		{2, RoleType_Mouse, 400, 300},
		{2, RoleType_Wolf, 350, 250},

		{3, RoleType_Wolf, 300, 200},
		{3, RoleType_Wolf, 400, 300},
		{3, RoleType_Scorpion, 300, 300},
		{3, RoleType_Scorpion, 400, 200},

		{5, RoleType_Ghost, 450, 350},
	},
	// 第二关，特点是敌人多，子弹密集。
	{
		{1, RoleType_Ant, 100, 100},
		{1, RoleType_Ant, 130, 130},
		{1, RoleType_Ant, 700, 100},
		{1, RoleType_Ant, 670, 130},
		{1, RoleType_Ant, 700, 500},
		{1, RoleType_Ant, 670, 470},
		{1, RoleType_Ant, 100, 500},
		{1, RoleType_Ant, 130, 470},

		{2, RoleType_Frog, 400, 300},
		{2, RoleType_Frog, 500, 400},
		{2, RoleType_Frog, 400, 400},
		{2, RoleType_Frog, 500, 300},

		{3, RoleType_Frog, 300, 200},
		{3, RoleType_Frog, 400, 300},
		{3, RoleType_Snake, 100, 100},
		{3, RoleType_Snake, 700, 100},
		{3, RoleType_Snake, 100, 500},

		{5, RoleType_FlameM, 450, 350},
	},
	// 第三关，敌人稀少、体积大伤害高。
	{
		{1, RoleType_Bee, 100, 100},
		{1, RoleType_Bee, 600, 400},

		{2, RoleType_Bee, 300, 200},
		{2, RoleType_Tortoise, 350, 250},

		{3, RoleType_Tiger, 350, 250},
		{3, RoleType_Tortoise, 250, 250},

		{5, RoleType_EDragon, 450, 350},
	},
};

////////////////// 玩家人物属性相关 ////////////////////////

struct _RoleData role_longxin = {
	"龙辛",
	"龙",
	"男，一个勇敢的探险家，四处冒险，写下了很多故事。但是如此诡秘的地牢，他还从来没有见过。虽然此处凶险，但也伴随机遇，他怎么可能放过呢？",
	30,
	0xff0288d1,
	0xff01579b,

	16,
	2,
	320,
};

float longxin_level_hp[3] = {10, 16, 22}; // 生命值、成长型数值
float longxin_level_atk[3] = {1, 2, 3};
float longxin_level_atkv[3] = {0.1, 0.06, 0.04};
double longxin_level_v[3] = {50, 50, 50};
double longxin_level_ext[3] = {1, 2, 4}; // 额外弹体、成长型数值

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

	12,
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
	2,
	50,
};

////////////////// 第一层boss ////////////////////////

struct _RoleData role_ghost = {
	"幽鬼",
	"鬼",
	"日积月累...不断吞噬...最后，它成为了一个怪物！一团巨大的恶鬼。恐怖、诡异的身影，成为了每个探索者的噩梦。",
	80,
	0xff444444,
	0xff000000,

	60,
	3,
	100,
};

struct _RoleData role_ghost_main = {
	"鬼魁",
	"魁",
	"幽鬼头领",
	40,
	0xff444444,
	0xff000000,

	60,
	3,
	220,
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
	16,
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
	0xff008837,
	0xff008837,

	20,
	4,
	50,
};

struct _RoleData role_snake = {
	"毒蛇",
	"蛇",
	"毒液有剧毒，喷射毒液杀死猎物后吞掉猎物。",
	20,
	0xff610000,
	0xff610000,

	12,
	3,
	0,
};

////////////////// 第二层boss ////////////////////////

struct _RoleData role_flamem = {
	"炎兽",
	"炎",
	"元素精灵，可以聚集周围的火元素，胆敢靠近者会被慢慢烧成灰烬。",
	70,
	0xffef6c00,
	0xffef6c00,

	220,
	4,
	100,
};

////////////////// 第三层怪物 ////////////////////////

struct _RoleData role_bee = {
	"杀人蜂",
	"蜂",
	"成群出没，具有强烈的毒性，牙齿可以咬穿皮革。",
	30,
	0xffffaa1f,
	0xffaa8800,

	10,
	10,
	100,
};

struct _RoleData role_tiger = {
	"虎拳",
	"虎",
	"高阶妖兽，半人半虎，擅长拳击。",
	40,
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
	30,
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
	5,
	120,
};

#endif