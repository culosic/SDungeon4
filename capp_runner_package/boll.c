#include "boll.h"

#include <base.h>
#include <ex_math.h>
#include <graphics.h>
#include <math.h>

#include "global.h"
#include "room.h"

Boll *bollsCreate(float r, int32 color, double v, double atkv) {
	Boll *head = create(sizeof(Boll));
	BollData *data = create(sizeof(BollData));
	head->data = data;
	data->r = r;
	data->color = color;
	data->v = v;
	data->atkv = atkv;
	return head;
}

void bollsDispose(Boll *head) {
	Boll *boll = (Boll *)head;
	dispose(head->data);
	do {
		Boll *prev = boll;
		boll = boll->next;
		dispose(prev);
	} while (boll);
}

void bollAdd(Boll *head, Role *role, float x, float y, double angle) {
	BollData *data = head->data;
	Boll *boll = create(sizeof(Boll));
	boll->role = role;
	boll->room = role->room;
	boll->vx = data->v * cos(angle);
	boll->vy = data->v * sin(angle);
	boll->x = x;
	boll->y = y;
	Boll *t = head;
	while (t->next) {
		t = t->next;
	}
	t->next = boll;
}

void bollUpdate(Boll *head, double t) {
	BollData *data = head->data;
	Boll *boll = head;
	Boll *prev;
	while (prev = boll, boll = boll->next) {
		Room *room = boll->room;
		if (room != room->map->currentRoom) {
			continue;
		}
		Role *enemy = NULL;
		RoomTile *tile = NULL;
		int dispear = false;
		boll->x += boll->vx * t;
		boll->y += boll->vy * t;
		if ((enemy = roomCollEnemy(room, boll->x, boll->y, data->r, boll->role))) {
			// 碰撞到角色，产生伤害。
			dispear = true;
			roleReduceHP(enemy, boll->role->data->atk);
		} else if ((tile = roomColl(boll->room, boll->x, boll->y, data->r))) {
			// 碰撞到墙壁。
			dispear = true;
		}
		if (dispear) {
			prev->next = boll->next;
			dispose(boll);
			boll = prev;
		}
	}
}

void bollDraw(Boll *head, double t) {
	BollData *data = head->data;
	Boll *boll = head;
	while ((boll = boll->next)) {
		Room *room = boll->room;
		if (room != room->map->currentRoom) {
			continue;
		}
		float x = room->px + boll->x;
		float y = room->py + boll->y;
		drawCir(x, y, data->r, data->color);
	}
}
