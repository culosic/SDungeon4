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

#endif