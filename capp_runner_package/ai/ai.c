#include "ai.h"

#include <base.h>

#include "../global.h"
#include "../role.h"
#include "../room.h"

float aiGetAngleToEnemy(Role *role, float scatterAngle) {
	Role *enemy = roomGetCloestEnemy(role->room, role);
	return (enemy ? getAngle(role->x, role->y, enemy->x, enemy->y) : role->faceAngle) + getRandScatter(scatterAngle);
}
