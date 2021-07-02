#include "boll.h"

#include <math.h>

#include "base.h"
#include "ex_math.h"
#include "graphics.h"

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
	while (prev = boll, boll = boll->next) {
		prev->next = boll->next;
		free(boll);
		boll = prev;
		// printf("remove boll\n");
	}
}

void bollAdd(Boll *head, float x, float y, float dx, float dy) {
	BollData *data = head->data;
	double v0 = 1000;
	double angle = 0;
	// TODO data->scattering * (rand() % (int)(M_PI * 50.0) / 50.0) * (rand() % 2 ? 1 : -1);
	int rightPart = dx > x ? 1 : -1;
	Boll *boll = malloc(sizeof(Boll));
	memset(boll, 0, sizeof(Boll));
	int sx = fabs(dx - x) < 1;
	int sy = fabs(dy - y) < 1;
	if (sx && !sy) {
		boll->vy = dy - y > 0 ? v0 : -v0;  // TODO
	} else if (!sx && sy) {
		boll->vx = dx - x > 0 ? v0 : -v0;
	} else {
		if (sx && sy) {
			angle += (rand() % (int)(M_PI * 100.0) / 200.0) * (rand() % 2 ? 1 : -1);
			rightPart = rand() % 2 ? 1 : -1;
		} else {
			angle += atan((dy - y) / (dx - x));
		}
		boll->vx = v0 * cos(angle) * rightPart;
		boll->vy = v0 * sin(angle) * rightPart;
	}
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
		// TODO 暂时为碰到屏幕i半圆就销毁。
		// if (!isCirCollRect(boll->x, boll->y, head->r, 0, 0, SCRW, SCRH)) {
		// 	prev->next = boll->next;
		// 	free(boll);
		// 	boll = prev;
		// 	// printf("remove boll\n");
		// }
	}
}

void bollDraw(Boll *head) {
	BollData *data = head->data;
	Boll *boll = head;
	Room *room = data->room;
	while (boll = boll->next) {
		float x = room->px + boll->x;
		float y = room->py + boll->y;
		drawCir(x, y, data->r, data->color);
	}
}
