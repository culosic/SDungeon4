#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"

int main() {
	srand(time(NULL));
	Map *map = mapInit(60);
	mapPrint(map);
	mapDispose(map);
	return 0;
}
