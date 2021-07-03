#include <math.h>
#include <stdio.h>

#include "test_global.c"
#include "tester.c"

int main() {
    test_global();
	printReport(1);
	testerDispose();
	return 0;
}