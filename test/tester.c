#include "tester.h"

#include <stdio.h>
#include <stdlib.h>

void testerDispose() {
    for (int i = 0; i < unpassedUnitCount; i++) {
        free(unpassedUnits[i]);
    }
}

static int addUnpassedUnit(char *message) {
	unpassedUnits[unpassedUnitCount++] = message;
	unitCount++;
	return 0;
}

static int addPpassedUnit() {
	unitCount++;
	return 1;
}

int equal(long actual, long expected, char *message) {
	int result;
	if (actual != expected) {
		char *msg = malloc(200 * sizeof(char));
		sprintf(msg, "%d\t%d\t%s", actual, expected, message);
		result = addUnpassedUnit(msg);
	} else {
		result = addPpassedUnit();
	}
}

int floatEqual(double actual, double expected, double minDeta, char *message) {
	int result;
	if (fabs(actual - expected) > minDeta) {
		char *msg = malloc(200 * sizeof(char));
		sprintf(msg, "%.3f\t%.3f\t%s", actual, expected, message);
		result = addUnpassedUnit(msg);
	} else {
		result = addPpassedUnit();
	}
	return result;
}

void printReport(int detail) {
	if (unpassedUnitCount) {
		printf("总共个%d用例，%d个不通过\n", unitCount, unpassedUnitCount);
	} else {
		printf("总共个%d用例，全部通过\n", unitCount);
	}
	if (detail && unpassedUnitCount) {
		printf("序\t实际\t期望\t信息\n", unitCount);
		for (int i = 0; i < unpassedUnitCount; i++) {
			printf("%d\t%s\n", i + 1, unpassedUnits[i]);
		}
	}
}