#ifndef _GAME_H_
#define _GAME_H_

#include "cirpad.h"
#include "map.h"
#include "role.h"

#define FPS 60.0
#define STAGEH 800

typedef struct _Game {
	int32 drawTimer;
	int32 drawLastTime;
	float fpsDT;
	float fps;

	struct _Map *map;
	struct _Role *mainRole;
	struct _Cirpad *dpad;
	struct _Cirpad *apad;
} Game;

Game game;

void gameUpdate(long data);
void gameEvent(int type, int p, int q);
void gameInit();
void gameDispose();

#endif