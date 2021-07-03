#include "cirpad.h"

#include "base.h"
#include "ex_math.h"
#include "global.h"
#include "graphics.h"

typedef struct _Cirpad {
	float x;
	float y;
	float r;
	float r2;
	double angle;
} Cirpad;

Cirpad cirpadCreate(float x, float y, float r, float r2) {
}

void cirpadDispose(Cirpad *cirpad) {
}

void cirpadUpdate(Cirpad *cirpad, double dt) {
}

void cirpadDraw(Cirpad *cirpad) {
}

int cirpadEvent(Cirpad *cirpad) {
}
