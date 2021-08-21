#include "map.h"

#include <base.h>
#include <graphics.h>
#include <math.h>

#include "ai/player/longxin.h"
#include "data.h"
#include "game.h"
#include "global.h"
#include "room.h"

Map *mapCreate() {
	// 初始化变量
	Map *map = create(sizeof(Map));

	// 创建主房间
	int roomX = 1, roomY = 1;
	int downOrRight = rand() % 2;
	int turnIndex = rand() % 5;
	map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomCreate(map, roomX, roomY, Room_Init);
	for (int i = 0; i < 5; i++) {
		if (i == turnIndex) {
			downOrRight = downOrRight == true ? false : true;
		}
		downOrRight ? roomY++ : roomX++;
		enum RoomType type;
		if (i == 4) {
			type = Room_Boss;
		} else if (i == 3) {
			type = Room_Prepare;
		} else {
			type = Room_Battle;
		}
		Room *room = map->roomList[map->roomCount++] = map->rooms[roomY][roomX] = roomCreate(map, roomX, roomY, type);
		Room *prev = room->prevRoom = map->roomList[map->roomCount - 2];
		room->linkRooms[room->linkRoomCount++] = prev;
		prev->linkRooms[prev->linkRoomCount++] = room;
	}
	map->bossRoom = map->roomList[5];

	// 查找次级房间的位置。
	int slots[100];
	int slotsSuper[100];
	int slotCount = 0;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int type = room->type;
		// printf("%s\n", room->caption);
		if (type == Room_Init || type == Room_Prepare || type == Room_Boss) {
			continue;  // 终点的boss房间和商店房间，不连接次级房间。
		}
		int x = room->x;
		int y = room->y;
		if (y > 0) {
			Room *top = map->rooms[y - 1][x];
			if (top == NULL) {
				slots[slotCount++] = x + (y - 1) * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y - 1][x] = roomCreate(map, x, y - 1, Room_Init);
			}
		}
		if (x < 9) {
			Room *right = map->rooms[y][x + 1];
			if (right == NULL) {
				slots[slotCount++] = x + 1 + y * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y][x + 1] = roomCreate(map, x + 1, y, Room_Init);
			}
		}
		if (y < 9) {
			Room *bottom = map->rooms[y + 1][x];
			if (bottom == NULL) {
				slots[slotCount++] = x + (y + 1) * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y + 1][x] = roomCreate(map, x, y + 1, Room_Init);
			}
		}
		if (x > 0) {
			Room *left = map->rooms[y][x - 1];
			if (left == NULL) {
				slots[slotCount++] = x - 1 + y * 10;
				slotsSuper[slotCount - 1] = i;
				// map->rooms[y][x - 1] = roomCreate(map, x - 1, y, Room_Init);
			}
		}
	}
	//printf("sc %d\n", slotCount);
	for (int i = 0; i < slotCount; i++) {
		int index = rand() % slotCount;
		int tmp = slots[i];
		int tmpSuper = slotsSuper[i];
		slots[i] = slots[index];
		slots[index] = tmp;
		slotsSuper[i] = slotsSuper[index];
		slotsSuper[index] = tmpSuper;
	}

	// 添加固定的次级房间。
	int staticIndex = 0;
	for (int i = 0; i < slotCount && staticIndex < 2; i++) {
		int x = slots[i] % 10;
		int y = slots[i] / 10;
		Room *slot = map->rooms[y][x];
		if (slot != NULL) {
			continue;  // 主房间的次级房间的位置可能有重叠，如果已创建房间，那么忽略重复位置。
		}
		enum RoomType type = room_gene_data_static[staticIndex];
		Room *room = map->roomList[map->roomCount++] = map->rooms[y][x] = roomCreate(map, x, y, type);
		Room *super = room->superRoom = map->roomList[slotsSuper[i]];
		room->linkRooms[room->linkRoomCount++] = super;
		super->linkRooms[super->linkRoomCount++] = room;
		staticIndex++;
	}

	map->currentRoom = map->roomList[0];
	for (int i = 0; i < map->roomCount; i++) {
		roomInitTile(map->roomList[i]);
	}

	return map;
}

void mapDispose(Map *map) {
	for (int i = 0; i < map->roomCount; i++) {
		roomDispose(map->roomList[i]);
	}
	dispose(map);
}

void mapDraw(Map *map, double t) {
	roomDraw(map->currentRoom, t);
}

static char *getBoxCaption(enum FuyinType type) {
	char *caption = NULL;
	switch (type) {
	case Fuyin_HP:
		caption = dialog_box_hp;
		break;
	case Fuyin_Atk:
		caption = dialog_box_atk;
		break;
	case Fuyin_AtkV:
		caption = dialog_box_atkv;
		break;
	case Fuyin_V:
		caption = dialog_box_v;
		break;
	case Fuyin_EXT:
		caption = dialog_box_ext;
		break;
	default:
		caption = "(err box)";
		break;
	}
	return caption;
}

static char *getBoxOpenedMsg(enum FuyinType type) {
	char *caption = NULL;
	switch (type) {
	case Fuyin_HP:
		caption = dialog_box_hp_opened;
		break;
	case Fuyin_Atk:
		caption = dialog_box_atk_opened;
		break;
	case Fuyin_AtkV:
		caption = dialog_box_atkv_opened;
		break;
	case Fuyin_V:
		caption = dialog_box_v_opened;
		break;
	case Fuyin_EXT:
		caption = dialog_box_ext_opened;
		break;
	default:
		caption = "(err box opened)";
		break;
	}
	return caption;
}

static void mapDrawMiniMap(Map *map, double t, int mapX, int mapY) {
	int c = 15;
	int d = 10;
	int doorw = 4;
	int cd = c + d;
	int x0 = 0, y0 = 0;
	int top = 0, right = 0, bottom = 0, left = 0;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int x = room->x;
		int y = room->y;
		if (i == 0) {
			top = y0 = y;
			right = x;
			bottom = y;
			left = x0 = x;
		} else {
			if (top > y)
				top = y0 = y;
			if (right < x)
				right = x;
			if (bottom < y)
				bottom = y;
			if (left > x)
				left = x0 = x;
		}
	}
	x0 = mapX - left * cd - (right + 1 - left) * cd * 0.5 + d * 0.5;
	y0 = mapY - top * cd - (bottom + 1 - top) * cd * 0.5 + d * 0.5;
	for (int i = 0; i < map->roomCount; i++) {
		Room *room = map->roomList[i];
		int x = x0 + room->x * cd;
		int y = y0 + room->y * cd;
		int active = map->currentRoom == room;
		int32 color = active ? 0xffe0e0e0 : 0xff888888;
		int32 linkColor = 0xff888888;
		switch (room->type) {
		case Room_Boss:
			color = active ? 0xffe00000 : 0xff880000;
			break;
		case Room_Potions:
			if (room->passed) {
				color = active ? 0xff1be020 : 0xff1b5e20;
			}
			break;
		case Room_Treasure:
			if (room->passed) {
				color = active ? 0xffe07700 : 0xff773300;
			}
			break;
		default:
			break;
		}
		drawRect(x, y, c, c, color);
		Room *linkRoom = room->prevRoom;
		if (linkRoom == NULL) {
			linkRoom = room->superRoom;
		}
		if (linkRoom != NULL) {
			if (room->x == linkRoom->x) {
				if (room->y > linkRoom->y) {
					drawRect(x + (c - doorw) / 2, y - d, doorw, d, linkColor);
				} else {
					drawRect(x + (c - doorw) / 2, y + c, doorw, d, linkColor);
				}
			} else if (room->y == linkRoom->y) {
				if (room->x > linkRoom->x) {
					drawRect(x - d, y + (c - doorw) / 2, d, doorw, linkColor);
				} else {
					drawRect(x + c, y + (c - doorw) / 2, d, doorw, linkColor);
				}
			}
		}
	}
}

void mapDrawUI(Map *map, double t) {
	RoomTile *tile = map->activeTile;
	// 各种弹窗提示。
	if (game.fail) {  // 角色死亡，游戏失败提示
		game.failT += t;
		if (game.failT > 3) {
			int w = 800, h = 600;
			int x = SCRW / 2 - w / 2;
			int y = SCRH / 2 - h / 2;
			int r = getShiningColor(0xff555555, 0xffe0e0e0, map->dialogContinueT += t, 1) % 256;
			drawRect(0, 0, SCRW, SCRH, 0xff212121);
			drawRect(x, y, w, h, 0xff555555);
			drawRect(x, y, w, 60, 0xffaaaaaa);
			drawTextC(dialog_loss_caption, x, y, w, 60, 33, 33, 33, 40);
			drawTextexC(dialog_loss_info, x, y + 60, w, 300, 204, 204, 204, 80, 20, 40);
			drawTextC(passed_screen_back, x, y + 300, w, 300, r, r, r, 40);
		}
	} else if (game.passed) {  // 过关提示
		game.passedT += t;
		if (game.passedT > 3) {
			int w = 800, h = 600;
			int x = SCRW / 2 - w / 2;
			int y = SCRH / 2 - h / 2;
			int r = getShiningColor(0xff555555, 0xffe0e0e0, map->dialogContinueT += t, 1) % 256;
			drawRect(0, 0, SCRW, SCRH, 0xff212121);
			drawRect(x, y, w, h, 0xff555555);
			drawRect(x, y, w, 60, 0xffaaaaaa);
			drawTextC(dialog_pass_caption, x, y, w, 60, 33, 33, 33, 40);
			if (game.floor >= -1) { // 第一层
				drawTextC(dialog_pass_info_levelup, x, y + 100, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_info_nextlevel_2, x, y + 160, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_next, x, y + 300, w, 300, r, r, r, 40);
			} else if (game.floor == -2) { // 第二层
				drawTextC(dialog_pass_info_levelup, x, y + 100, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_info_nextlevel_3, x, y + 160, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_next, x, y + 300, w, 300, r, r, r, 40);
			} else { // 最后一层
				drawTextC(dialog_pass_info_allwin, x, y + 100, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_info_found, x, y + 160, w, 60, 204, 204, 204, 40);
				drawTextC(dialog_pass_end, x, y + 300, w, 300, r, r, r, 40);
			}
		}
	} else if (tile) {
		if (tile->type == RoomTile_Potions && tile->potionsTextT > 0) {  // 治疗提示
			uint16 c = getShiningColor(0xffaaaaaa, 0xff000000, tile->potionsTextT, 0.5) % 256;
			int b = 3;
			drawRect(0, 100, SCRW, 60, 0xff333333);
			drawRect(0, 100 + b, SCRW, 60 - b * 2, 0xffaaaaaa);
			drawTextC(toast_heal, 0, 100, SCRW, 60, c, c, c, 40);
		} else if (tile->type == RoomTile_Treasure && tile->boxVisible) {	// 宝箱弹窗
			int w = 800, h = 600;
			int x = SCRW / 2 - w / 2;
			int y = SCRH / 2 - h / 2;
			int d = 3;
			drawRect(0, 0, SCRW, SCRH, 0x88333333);
			drawRect(x, y, w, h, 0xcc555555);
			drawRect(x, y, w, 60, 0xffaaaaaa);
			drawTextC(dialog_box_caption, x, y, w, 60, 33, 33, 33, 40);
			drawTextexC(dialog_box_info, x, y + 60, w, 300, 204, 204, 204, 80, 20, 40);
			drawRect(x + w / 2 - 250, y + h - 350, 200, 200, 0xffbd6c2e);
			drawRect(x + w / 2 - 250 + d, y + h - 350 + d, 200 - d * 2, 200 - d * 2, 0xff773300);
			drawTextC(getBoxCaption(map->boxSelect1), x + w / 2 - 250, y + h - 350, 200, 200, 255, 213, 79, 40);
			drawRect(x + w / 2 + 50, y + h - 350, 200, 200, 0xffbd6c2e);
			drawRect(x + w / 2 + 50 + d, y + h - 350 + d, 200 - d * 2, 200 - d * 2, 0xff773300);
			drawTextC(getBoxCaption(map->boxSelect2), x + w / 2 + 50, y + h - 350, 200, 200, 255, 213, 79, 40);
		} else if (map->boxOpenT > 0) {	 // 宝箱已获取的提示
			int b = 3;
			map->boxOpenT = fmax(0, map->boxOpenT - t);
			drawRect(0, 100, SCRW, 60, 0xff333333);
			drawRect(0, 100 + b, SCRW, 60 - b * 2, 0xffaaaaaa);
			drawTextC(getBoxOpenedMsg(map->boxSelectIndex == 1 ? map->boxSelect1 : map->boxSelect2), 0, 100, SCRW, 60, 0, 0, 0, 40);
		}
	}
	// 左上角属性栏
	int rd = 100;
	static char mrole_hp[50], mrole_others[50];
	drawRect(0, 0, 500, rd, 0xee333333);
	drawRect(0, 0, rd, rd, 0xff555555);
	drawTextC(game.mainRole->data->caption, 0, 0, rd, rd, 255, 255, 255, 40);
	sprintf(mrole_hp, headinfo_hp, (int)round(game.mainRole->hp), (int)round(game.mainRole->hps));
	drawTextC(mrole_hp, rd, 0, 400, rd / 2, 204, 204, 204, 30);
	sprintf(mrole_others, headinfo_others, (int)round(game.mainRole->atk), 1 / game.mainRole->atkv, (int)round(game.mainRole->v));
	drawTextC(mrole_others, rd, rd / 2, 400, rd / 2, 204, 204, 204, 30);
	// 右上角地图
	int md = 160;
	int mapX = SCRW - md;
	drawRect(mapX, 0, md, md, 0xee333333);
	mapDrawMiniMap(map, t, mapX + md / 2, md / 2);
	// boss演出
	if (map->bossPreShow) {
		Room *room = map->currentRoom;
		Role *boss = room->roles[0];
		int T = 1;
		float p = fmin(1, map->bossT / T);
		float y = room->py + boss->y;
		float h1 = (y - boss->data->r - 50);
		float h2 = (SCRH - (y + boss->data->r + 50));
		h1 *= -p * (p - 2);
		h2 *= -p * (p - 2);
		map->bossT += t;
		drawRect(0, 0, SCRW, h1, 0xff000000);
		drawRect(0, SCRH - h2, SCRW, h2, 0xff000000);
		drawTextC(boss->data->name, 0, 0, SCRW, h1, 235, 235, 235, 80);
		drawTextexC(boss->data->info, 0, SCRH - h2, SCRW / 2, SCRH, 235, 235, 235, 100, 50, 40);
		if (p >= 1) {
			uint16 c = getShiningColor(0xff000000, 0xffe8e8e8, map->bossT - T, 1) % 256;
			drawTextC(boss_start, SCRW / 2, SCRH - h2, SCRW / 2, h2, c, c, c, 40);
		}
	}
}

static void mapUpdatePassOrFail(Map *map, double t) {
	Room *room = map->bossRoom;
	if (!room->roleCount) {
		return;
	}
	if (game.mainRole->hp > 0) {
		int passed = true;
		for (int i = 0; i < room->roleCount; i++) {
			Role *role = room->roles[i];
			if (role->enemy && role->hp > 0) {
				passed = false;
				break;
			}
		}
		if (!game.passed && passed) {
			game.passed = true;
			game.userControll = false;
			// 过关后提升主角属性。
			game.mainRole->hp += 14;
			game.mainRole->hps += 14;
			game.mainRole->atk++;
			game.mainRole->boll->data->r += 2;
			game.mainRole->atkv = game.mainRole->boll->data->atkv = fmax(0.1, game.mainRole->boll->data->atkv - 0.05);
		}
	} else if (!game.fail) {
		game.fail = true;
		game.userControll = false;
	}
	if ((game.fail && game.failT > 3) || (game.passed && game.passedT > 3)) {
		// 继续慢动作一段时间后停止
		roleStopMove(game.mainRole);
		roleStopAttack(game.mainRole);
	}
}

void mapUpdate(Map *map, double t) {
	if (map->bossPreShow) {
		return;	 // boss演出中，暂停。
	}
	if ((game.fail && game.failT <= 3) || (game.passed && game.passedT <= 3)) {
		// 慢动作效果
		t *= 0.25;
	}
	roomUpdate(map->currentRoom, t);
	mapUpdatePassOrFail(map, t);
}

void mapEvent(Map *map, int type, int p, int q) {
	RoomTile *tile = map->activeTile;
	if (tile) {
		if (tile->boxVisible) {	 // 宝箱弹窗
			int w = 800, h = 600;
			int x = SCRW / 2 - w / 2;
			int y = SCRH / 2 - h / 2;
			if (type == MS_UP) {
				int opened = false;
				if (isPointCollRect(p, q, x + w / 2 - 250, y + h - 350, 200, 200)) {
					// 选择1
					opened = true;
					map->boxSelectIndex = 1;
					aiLongxinAddLevel(game.mainRole->ai, map->boxSelect1);
				} else if (isPointCollRect(p, q, x + w / 2 + 50, y + h - 350, 200, 200)) {
					// 选择2
					opened = true;
					map->boxSelectIndex = 2;
					aiLongxinAddLevel(game.mainRole->ai, map->boxSelect2);
				}
				if (opened) {
					map->boxOpenT = 2;
					tile->boxOpened = true;
					tile->boxVisible = false;
					game.userControll = true;
				}
			}
		}
	}
	if (game.fail && game.failT > 4) {	// 游戏结束，点击继续返回主菜单
		static int failD = false;
		if (type == MS_DOWN) {
			failD = true;
		} else if (type == MS_UP && failD) {
			failD = false;
			game.nextScreen = Screen_Init;
		}
	} else if (game.passed && game.passedT > 4) {  // 过关，点击进入下一关
		static int passedD = false;
		if (type == MS_DOWN) {
			passedD = true;
		} else if (type == MS_UP && passedD) {
			passedD = false;
			if (game.floor > -3) {
				game.nextScreen = Screen_Down;
			} else {  // 目前只有三关，第三关通过后通关。
				game.nextScreen = Screen_Passed;
			}
		}
	} else if (map->bossPreShow && map->bossT > 1) {  // boss演出，开始战斗
		static int startD = false;
		if (type == MS_DOWN) {
			startD = true;
		} else if (type == MS_UP && startD) {
			startD = false;
			map->bossT = 0;
			map->bossPreShow = false;
			game.userControll = true;
		}
	}
}
