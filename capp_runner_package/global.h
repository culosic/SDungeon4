#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

/**
 * 将utf-8转为gb2312字符串。手机c绘制utf-8会乱码，所以必须转成gb2312再绘制。
 */
char* utf8_c(char* c);
/**
 * 在一个区域内居中绘制文字。
 */
void drawTextC(char* c, int x, int y, int w, int h, int r, int g, int b, int textSize);
/**
 * @brief 计算向量角度
 * 
 * @param x0 起始x位置
 * @param y0 起始y位置
 * @param x1 指向x位置
 * @param y1 指向y位置
 * @return 弧度制，与x周逆时针夹角，值域[0，π]
 */
float getAngle(float x0, float y0, float x1, float y1);

#endif