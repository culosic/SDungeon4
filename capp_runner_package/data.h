#ifndef _DATA_H_
#define _DATA_H_

#include <base.h>

#include "role.h"
#include "room.h"

/////////////////// �������� ////////////////////////

char *init_screen_caption = "S����";
char *init_screen_text1 = "����";
char *init_screen_start = "��ʼ��Ϸ";
char *init_screen_exit = "�˳�";

char *down_screen_ing = "��¥��...";

char *passed_screen_caption = "��ͨ�أ���л����";  // TODO ���ͨ���ݳ���ɾ����

char *passed_screen_story[10] = {
	"�����Ѿ������顢����Ϊ��һ�������ߡ�",
	"��Ը���ܼ��ر��ġ�",
};

char *passed_screen_fly[10] = {
	"�����Ѿ�̮����ֻ�ܿ��Ա�һ������Ķ�Ѩ����",
	"���õ��ģ����и���������е�����",
	"�����Ѿ�������ȥѰ�������Լ���·��",
};

char *passed_screen_thanks = "��ϲͨ�� ��л����";

char *passed_screen_info[10] = {
	"����   ������",
	"����   ��",
	"����   ��",
};

char *passed_screen_ps[10] = {
	"�����ķǳ���л�����浽���",
	"�����Ϸ��Ȼ�ǳ�����",
	"Ҳû������������",
	"�Һķ�����ྫ��",
	"��Ը�ܸ�����Ϸ�������һ������",
};

char *passed_screen_back = "������Ļ�������˵�";

////////////////// ��ͼ���� /////////////////////////

char *room_init_caption = "��";
char *room_battle_caption = "ս";
char *room_potions_caption = "ҩ";
char *room_treasure_caption = "��";
char *room_boss_caption = "��";

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

// ����¥���������
FloorRole floor_enemies[4][100] = {
	{
		{1, RoleType_Mouse, 100, 100},
		{1, RoleType_Mouse, 600, 100},
		{1, RoleType_Mouse, 600, 400},
		{1, RoleType_Mouse, 100, 400},
		{1, RoleType_Mouse, 350, 250},

		{2, RoleType_Mouse, 300, 200},
		{2, RoleType_Mouse, 400, 300},
		{2, RoleType_Wolf, 350, 250},

		{3, RoleType_Wolf, 300, 200},
		{3, RoleType_Wolf, 400, 300},
		{3, RoleType_Scorpion, 300, 300},
		{3, RoleType_Scorpion, 400, 200},

		{4, RoleType_Ghost, 450, 350},
	},
	{
		{1, RoleType_Ant, 100, 100},
		{1, RoleType_Ant, 600, 100},
		{1, RoleType_Ant, 600, 400},
		{1, RoleType_Ant, 100, 400},
		{1, RoleType_Ant, 350, 250},

		{2, RoleType_Ant, 300, 200},
		{2, RoleType_Ant, 400, 300},
		{2, RoleType_Frog, 350, 250},

		{3, RoleType_Frog, 300, 200},
		{3, RoleType_Frog, 400, 300},
		{3, RoleType_Snake, 300, 300},
		{3, RoleType_Snake, 400, 200},

		{4, RoleType_FlameM, 450, 350},
	},
	{
		{1, RoleType_Bee, 100, 100},
		{1, RoleType_Bee, 600, 100},
		{1, RoleType_Bee, 600, 400},
		{1, RoleType_Bee, 100, 400},
		{1, RoleType_Bee, 350, 250},

		{2, RoleType_Bee, 300, 200},
		{2, RoleType_Bee, 400, 300},
		{2, RoleType_Tiger, 350, 250},

		{3, RoleType_Tiger, 300, 200},
		{3, RoleType_Tiger, 400, 300},
		{3, RoleType_Tortoise, 300, 300},
		{3, RoleType_Tortoise, 400, 200},

		{4, RoleType_EDragon, 450, 350},
	},
};

////////////////// �������������� ////////////////////////

struct _RoleData role_longxin = {
	"����",
	"��",
	"�У�һ���¸ҵ�̽�ռң��Ĵ�ð�գ�д���˺ܶ���¡�������˹��صĵ��Σ���������û�м�������Ȼ�˴����գ���Ҳ�������������ô���ܷŹ��أ�",
	30,
	0xff0288d1,
	0xff01579b,

	10,
	2,
	300,
};

////////////////// ��һ����� ////////////////////////

struct _RoleData role_mouse = {
	"�����",
	"��",
	"���ζ���¥�����洦�ɼ������󣬿��Ը���Ϊ�������Է��丯ʴ�ԵĶ�Һ����Ŀ�ꡣ",
	20,
	0xff996b1f,
	0xff663300,

	6,
	1,
	150,
};

struct _RoleData role_wolf = {
	"����",
	"��",
	"���ݡ��׺���һ������ɭ�֣����˵���Ѱ�������Щ��̽�����ε�����;����������",
	25,
	0xff666666,
	0xff333333,

	12,
	3,
	200,
};

struct _RoleData role_scorpion = {
	"��Ы",
	"Ы",
	"�����г��������ޣ����ͽϴ󣬿��Է��䶾Һ���������ս������ǿ��",
	35,
	0xff9966cc,
	0xff6633aa,

	15,
	3,
	100,
};

////////////////// ��һ��boss ////////////////////////

struct _RoleData role_ghost = {
	"�Ĺ�",
	"��",
	"�ջ�����...��������...�������Ϊ��һ�����һ�ž޴�Ķ���ֲ����������Ӱ����Ϊ��ÿ��̽���ߵ�ج�Ρ�",
	60,
	0xff444444,
	0xff000000,

	60,
	3,
	100,
};

struct _RoleData role_ghost_main = {
	"����",
	"��",
	"�Ĺ�ͷ��",
	40,
	0xff444444,
	0xff000000,

	60,
	3,
	200,
};

struct _RoleData role_ghost_child = {
	"�n��",
	"�n",
	"�Ĺ���",
	20,
	0xff444444,
	0xff000000,

	4,
	1,
	300,
};

////////////////// �ڶ������ ////////////////////////

struct _RoleData role_ant = {
	"��ʴ��",
	"��",
	"��Ⱥ��û�������з��ڵ�ǿ����Һ��ʳ���",
	12,
	0xff332200,
	0xff332200,

	8,
	2,
	100,
};

struct _RoleData role_frog = {
	"����",
	"��",
	"���Խ�ǿ��ͬʱ�ó�Ծ����",
	25,
	0xff22aa37,
	0xff008837,

	20,
	8,
	150,
};

struct _RoleData role_snake = {
	"����",
	"��",
	"��Һ�о綾�����䶾Һɱ��������̵����",
	20,
	0xff800000,
	0xff610000,

	12,
	5,
	0,
};

////////////////// �ڶ���boss ////////////////////////

struct _RoleData role_flamem = {
	"����",
	"��",
	"Ԫ�ؾ��飬���Ծۼ���Χ�Ļ�Ԫ�أ����ҿ����߻ᱻ�����ճɻҽ���",
	70,
	0xffff7700,
	0xff663300,

	220,
	3,
	100,
};

////////////////// ��������� ////////////////////////

struct _RoleData role_bee = {
	"ɱ�˷�",
	"��",
	"��Ⱥ��û������ǿ�ҵĶ��ԣ����ݿ���ҧ��Ƥ�",
	20,
	0xffffaa1f,
	0xffaa8800,

	10,
	8,
	150,
};

struct _RoleData role_tiger = {
	"��ȭ",
	"��",
	"�߽����ޣ����˰뻢���ó�ȭ����",
	30,
	0xffffffff,
	0xff999999,

	30,
	16,
	200,
};

struct _RoleData role_tortoise = {
	"����",
	"��",
	"�߽����ޣ���׼�Ӳ�ޱ�",
	60,
	0xff99aacc,
	0xff607d8b,

	100,
	0,
	50,
};

////////////////// ������boss ////////////////////////

struct _RoleData role_edragon = {
	"����������",
	"��",
	"�����һԱ����ҹ���ڴ��и�����������ôҲ�ò������С�",
	80,
	0xff000000,
	0xff000000,

	300,
	4,
	200,
};

#endif