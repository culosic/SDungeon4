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
 * @brief 绘制文本。
 * 
 * @param c 文本内容
 * @param x 文字显示x位置
 * @param y 文字显示y位置
 * @param r 颜色r
 * @param g 颜色g
 * @param b 颜色b
 * @param textSize 字体大小
 */
void drawText(char* c, int x, int y, int r, int g, int b, int textSize);

/**
 * @brief 绘制文本。文本会居中显示到制定矩形区域里。
 * 
 * @param c 文本内容
 * @param x 指定绘制区域x位置
 * @param y 指定绘制区域y位置
 * @param w 指定绘制区域宽
 * @param h 指定绘制区域高
 * @param r 颜色r
 * @param g 颜色g
 * @param b 颜色b
 * @param textSize 字体大小
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