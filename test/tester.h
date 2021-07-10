#ifndef _TESTER_H_
#define _TESTER_H_

#define FLOAT_MIN_DT 0.001
#define MAX_ERR_COUNT 100

char *unpassedUnits[MAX_ERR_COUNT];
int unpassedUnitCount = 0;
int unitCount = 0;

void testerDispose();
int equal(long a, long b, char *message);
int notEqual(long a, long b, char *message);
int floatEqual(double a, double b, double minDeta, char *message);
int notFloatEqual(double a, double b, double minDeta, char *message);
void printReport(int detail);

#endif