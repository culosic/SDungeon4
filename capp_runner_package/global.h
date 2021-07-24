#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <base.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

long create_times = 0;

long dispose_times = 0;

/**
 * @brief 申请内存并清零。必须用dispose释放。程序结束后会计算有没有泄露内存。
 */
void* create(int32 size);

/**
 * @brief 释放由create函数申请的内存。
 */
void dispose(void* address);

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
 * @param color 颜色
 * @param textSize 字体大小
 */
void drawText(char *c, int x, int y, int32 color, int textSize);

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
 * @brief 同drawTextC，可以换行。
 */
void drawTextexC(char *c, int x, int y, int w, int h, int r, int g, int b, int indent, int padding, int textSize);

/**
 * @brief 改变透明度并返回颜色
 */
int32 getAlphaColor(int32 color, float alpha);

/**
 * @brief 计算向量角度
 * 
 * @param x0 起始x位置
 * @param y0 起始y位置
 * @param x1 指向x位置
 * @param y1 指向y位置
 * @return 弧度制，与x周逆时针夹角，值域[0，2π]
 */
float getAngle(float x0, float y0, float x1, float y1);

/**
 * @brief 获得一个随机的角度
 * 
 * @return 弧度制，值域[0，2π]
 */
float getRandAngle();

/**
 * @brief 获得一个随机的偏角
 * 
 * @return 弧度制，值域[-angle，angle]
 */
float getRandScatter(float angle);

/**
 * @brief 返回一个随机小数
 */
float getRandFloat(float from, float to);

/**
 * @brief 获取一个随时间变化的闪烁的颜色，暂不支持透明度变化
 * 
 * @param color1 初始颜色
 * @param color2 半周期后的颜色
 * @param t 闪烁计时
 * @param duration 闪烁变化半周期
 * @return 颜色，在时间[0, duration]里由color1变为color2，[duration, duration * 2]里再变为color1，如此往复。
 */
int32 getShiningColor(int32 color1, int32 color2, double t, double duration);

#endif