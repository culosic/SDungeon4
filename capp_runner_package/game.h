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

	Map *map;
	Role *role;
	Cirpad *dpad;
	Cirpad *apad;
} Game;

Game game;

void gameDrawFPS(float t);
void gameUpdate(long data);
void gameEvent(int type, int p, int q);
void gameInit();
void gameDispose();

#endif