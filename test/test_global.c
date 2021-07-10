#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tester.h"

// // 逆时针
// float getAngle(float x0, float y0, float x1, float y1) {
// 	float dx = x1 - x0, dy = y1 - y0;
// 	float r = 0;
// 	if (dx == 0) {	// y轴方向
// 		if (dy > 0) {
// 			r = M_PI * 0.5;
// 		} else if (dy < 0) {
// 			r = M_PI * 1.5;
// 		}
// 	} else if (dy == 0) {  // x轴方向
// 		if (dx > 0) {
// 			r = 0;
// 		} else if (dx < 0) {
// 			r = M_PI;
// 		}
// 	} else if (dy > 0) {  // 第一二象限
// 		r = dx > 0 ? atan(dy / dx) : (-atan(dx / dy) + M_PI * 0.5);
// 	} else {  // 第三四象限
// 		r = dx < 0 ? (atan(dy / dx) + M_PI) : (-atan(dx / dy) + M_PI * 1.5);
// 	}
// 	return r;
// }

// 顺时针
float getAngle(float x0, float y0, float x1, float y1) {
	float dx = x1 - x0, dy = y1 - y0;
	float r = 0;
	if (dx == 0) {	// y轴方向
		if (dy < 0) {
			r = M_PI * 0.5;
		} else if (dy > 0) {
			r = M_PI * 1.5;
		}
	} else if (dy == 0) {  // x轴方向
		if (dx > 0) {
			r = 0;
		} else if (dx < 0) {
			r = M_PI;
		}
	} else if (dy > 0) {  // 第一二象限
		r = dx > 0 ? atan(dy / dx) : (-atan(dx / dy) + M_PI * 0.5);
	} else {  // 第三四象限
		r = dx < 0 ? (atan(dy / dx) + M_PI) : (-atan(dx / dy) + M_PI * 1.5);
	}
	return r;
}

typedef struct _TestMemset {
	int b[10];
} TestMemset;

// malloc后memset数组
void testMallocaAndMemset() {
	TestMemset *obj = malloc(sizeof(TestMemset));
	void* oldB = obj->b;
	memset(obj, 0, sizeof(obj));
	equal(sizeof(TestMemset), 40, "结构体的大小包含数组大小");
	equal(sizeof(obj), 4, "结构体对象的大小，不包含数组大小");
	equal((long)obj->b, (long)oldB, "memset之后，结构体里的数组指针应该不变化。");
	free(obj);
}

unsigned int getAlphaColor(unsigned int color, float alpha) {
	unsigned int a = ((int)(255 * alpha)) << 24;
	return (color & a) + (color ^ 0xff000000);
}

void test_global() {
	floatEqual(getAngle(0, 0, 0, 0), 0, FLOAT_MIN_DT, "测试零向量");
	floatEqual(getAngle(0, 0, 1, 0), 0, FLOAT_MIN_DT, "测试右向量");
	floatEqual(getAngle(0, 0, 0, -1), M_PI * 0.5, FLOAT_MIN_DT, "测试上向量");
	floatEqual(getAngle(0, 0, -1, 0), M_PI, FLOAT_MIN_DT, "测试左向量");
	floatEqual(getAngle(0, 0, 0, 1), M_PI * 1.5, FLOAT_MIN_DT, "测试下向量");
	floatEqual(getAngle(0, 0, sqrt(3), 1), M_PI / 6, FLOAT_MIN_DT, "测试30°");
	floatEqual(getAngle(0, 0, -1, sqrt(3)), M_PI * 0.5 + M_PI / 6, FLOAT_MIN_DT, "测试120°");
	floatEqual(getAngle(0, 0, -sqrt(3), -1), M_PI + M_PI / 6, FLOAT_MIN_DT, "测试210°");
	floatEqual(getAngle(0, 0, 1, -sqrt(3)), M_PI * 1.5 + M_PI / 6, FLOAT_MIN_DT, "测试300°");

	testMallocaAndMemset();

	floatEqual(getAlphaColor(0xff112233, 0.1), 0x19000000 + 0x00112233, FLOAT_MIN_DT, "测试alpha0.1的颜色");
}