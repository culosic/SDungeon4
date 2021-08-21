#ifndef _DATA_H_
#define _DATA_H_

#include <base.h>

#include "role.h"
#include "room.h"

/////////////////// �������� ////////////////////////

char *init_screen_caption = "S����";
char *init_screen_text1 = "����";
char *init_screen_author = "��������Ʒ(v0.4.5)";
char *init_screen_start = "��ʼ��Ϸ";
char *init_screen_exit = "�˳�";

char *down_screen_ing = "��¥��...";

char *game_screen_exit_caption = "\x7e\xd3\x67\x5f\x0\x0";
char *game_screen_exit_info = "\x8f\xd4\x56\xde\x4e\x3b\x83\xdc\x53\x55\x4f\x1a\x4e\x22\x59\x31\x6e\x38\x62\xf\x8f\xdb\x5e\xa6\xff\xc\x78\x6e\x5b\x9a\x89\x81\x8f\xd4\x56\xde\x54\x17\xff\x1f\x0\x0";

char *passed_screen_story[10] = {
	"�����Ѿ������顢��Ϊ��һ�������ߡ�",
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

////////////////// ���桢������Ϣ /////////////////////////

char *headinfo_hp = "���� %d/%d";
char *headinfo_others = "�� %d ���� %.1f ���� %d";
char *mapinfo_caption = "ͼ";

char *dialog_box_caption = "����";
char *dialog_box_info = "������������з�ӡ�����ԣ����������ѡ�����е�һ�֣�";
char *dialog_box_hp = "��ʯ";
char *dialog_box_hp_opened = "������������";
char *dialog_box_atk = "�ƻ�";
char *dialog_box_atk_opened = "����������";
char *dialog_box_atkv = "����";
char *dialog_box_atkv_opened = "�����ٶ�����";
char *dialog_box_v = "����";
char *dialog_box_v_opened = "�ƶ��ٶ�����";
char *dialog_box_ext = "�޾�";
char *dialog_box_ext_opened = "��Ļ��������";

char *dialog_loss_caption = "����";
char *dialog_loss_info = "���������ĵ����У����������ˣ����ջ��ǵ����ˡ���";
char *dialog_loss_back = "������Ļ�������˵�";

char *dialog_pass_caption = "ʤ��";
char *dialog_pass_info_levelup = "������������������١���������";
char *dialog_pass_info_nextlevel_2 = "����һ�㡿��������գ�Ұ���ܼ�";
char *dialog_pass_info_nextlevel_3 = "�����ǡ����һ�㡿������ǿ��ϡ��";
char *dialog_pass_info_allwin = "���ܡ����յ��ز��ߡ���";
char *dialog_pass_info_found = "�㷢���˴�����ַ����";
char *dialog_pass_next = "������Ļ������һ��";
char *dialog_pass_end = "������Ļ����";

char *toast_heal = "������";

char *boss_start = "������Ļ��ʼս��";

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
	// ��һ�ء�boss��������̬
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
	// �ڶ��أ��ص��ǵ��˶࣬�ӵ��ܼ���
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
	// �����أ�����ϡ�١�������˺��ߡ�
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

////////////////// �������������� ////////////////////////

struct _RoleData role_longxin = {
	"����",
	"��",
	"�У�һ���¸ҵ�̽�ռң��Ĵ�ð�գ�д���˺ܶ���¡�������˹��صĵ��Σ���������û�м�������Ȼ�˴����գ���Ҳ�������������ô���ܷŹ��أ�",
	30,
	0xff0288d1,
	0xff01579b,

	16,
	2,
	320,
};

float longxin_level_hp[3] = {10, 16, 22}; // ����ֵ���ɳ�����ֵ
float longxin_level_atk[3] = {1, 2, 3};
float longxin_level_atkv[3] = {0.1, 0.06, 0.04};
double longxin_level_v[3] = {50, 50, 50};
double longxin_level_ext[3] = {1, 2, 4}; // ���ⵯ�塢�ɳ�����ֵ

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
	2,
	50,
};

////////////////// ��һ��boss ////////////////////////

struct _RoleData role_ghost = {
	"�Ĺ�",
	"��",
	"�ջ�����...��������...�������Ϊ��һ�����һ�ž޴�Ķ���ֲ����������Ӱ����Ϊ��ÿ��̽���ߵ�ج�Ρ�",
	80,
	0xff444444,
	0xff000000,

	60,
	3,
	100,
};

struct _RoleData role_ghost_main = {
	"���",
	"��",
	"�Ĺ�ͷ��",
	40,
	0xff444444,
	0xff000000,

	60,
	3,
	220,
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
	16,
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
	0xff008837,
	0xff008837,

	20,
	4,
	50,
};

struct _RoleData role_snake = {
	"����",
	"��",
	"��Һ�о綾�����䶾Һɱ��������̵����",
	20,
	0xff610000,
	0xff610000,

	12,
	3,
	0,
};

////////////////// �ڶ���boss ////////////////////////

struct _RoleData role_flamem = {
	"����",
	"��",
	"Ԫ�ؾ��飬���Ծۼ���Χ�Ļ�Ԫ�أ����ҿ����߻ᱻ�����ճɻҽ���",
	70,
	0xffef6c00,
	0xffef6c00,

	220,
	4,
	100,
};

////////////////// ��������� ////////////////////////

struct _RoleData role_bee = {
	"ɱ�˷�",
	"��",
	"��Ⱥ��û������ǿ�ҵĶ��ԣ����ݿ���ҧ��Ƥ�",
	30,
	0xffffaa1f,
	0xffaa8800,

	10,
	10,
	100,
};

struct _RoleData role_tiger = {
	"��ȭ",
	"��",
	"�߽����ޣ����˰뻢���ó�ȭ����",
	40,
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
	30,
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
	5,
	120,
};

#endif