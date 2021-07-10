#include "boll.h"

#include <math.h>

#include "base.h"
#include "ex_math.h"
#include "graphics.h"
#include "room.h"

Boll *bollCreates(Room *room, float r, int32 color, double v, float range) {
	Boll *head = malloc(sizeof(Boll));
	BollData *data = malloc(sizeof(Boll));
	memset(head, 0, sizeof(Boll));
	memset(data, 0, sizeof(BollData));
	head->data = data;
	data->room = room;
	data->r = r;
	data->color = color;
	data->v = v;
	data->range = range;
	return head;
}

void bollDispose(Boll *head) {
	Boll *boll = (Boll *)head;
	Boll *prev;
	free(head->data);  // TODO 这个data应该游戏结束后销毁
	while (prev = boll, boll = boll->next) {
		prev->next = boll->next;
		free(boll);
		boll = prev;
		// printf("remove boll\n");
	}
}

void bollAdd(Boll *head, float x, float y, double angle) {
	// BollData *data = head->data;
	double v0 = 600;  // TODO 速度放入data。
	Boll *boll = malloc(sizeof(Boll));
	memset(boll, 0, sizeof(Boll));
	boll->vx = v0 * cos(angle);
	boll->vy = v0 * sin(angle);
	boll->x = x;
	boll->y = y;
	Boll *t = head;
	while (t->next) {
		t = t->next;
	}
	t->next = boll;
	// printf("add boll at (%.1f, %.1f)\n", x, y);
}

void bollUpdate(Boll *head, double t) {
	BollData *data = head->data;
	Boll *boll = head;
	Boll *prev;
	while (prev = boll, boll = boll->next) {
		boll->x += boll->vx * t;
		boll->y += boll->vy * t;
		// 碰撞墙壁、超出射程旧销毁
		// TODO 暂时设为超出就销毁。
		if (!isCirCollRect(boll->x, boll->y, data->r, 0, 0, SCRW, SCRH)) {
			prev->next = boll->next;
			free(boll);
			boll = prev;
			// printf("remove boll\n");
		}
	}
}

void bollDraw(Boll *head) {
	BollData *data = head->data;
	Boll *boll = head;
	Room *room = data->room;
	while ((boll = boll->next)) {
		float x = room->px + boll->x;
		float y = room->py + boll->y;
		drawCir(x, y, data->r, data->color);
	}
}
