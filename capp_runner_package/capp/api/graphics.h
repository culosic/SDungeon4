/**
 * 手机c绘图相关接口
 */

#include <base.h>

// 保存图片的类型
enum {
	_JPG = 0,
	_PNG = 1,
	_BMP16 = 2
};

// bmp图片信息
typedef struct
{
	uint32 width;	// 宽度
	uint32 height;	// 高度
	uint32 stride;
	int32 format;  // 格式
	uint32 flags;  // 0 for now
	void *ptr;	   // 缓存
} BITMAPINFO;

/**
 * 创建bitmap
 * @param width 图片宽度
 * @param height 图片高度
 * @returns >0表示创建成功，返回bitmap句柄，-1表示失败
 */
int createBitmap(int w, int h);

/**
 * 读取一张图片
 * @param filename 文件名
 * @returns 0表示读取成功，返回bitmap句柄，-1表示失败
 */
int32 readBitmap(char *filename);

/**
 * 从apk安装包assets目录读取图片。
 * @param filename 文件名
 * @returns >0表示读取成功，返回bitmap句柄；-1表示失败
 */
int32 readBitmapFromAssets(char *filename);

/**
 * 裁剪b中(x,y,w,h)部分生成新的bitmap。
 * 这个函数是回调的安卓接口，当裁剪图片和原图片一样大，返回原图片，当裁剪图片是原图的一部分，重新创建一张图片。
 * @param b bitmap句柄
 * @param x 裁剪的x坐标
 * @param y 裁剪的y坐标
 * @param w 裁剪区域宽度
 * @param h 裁剪区域高度
 * @returns >0表示裁剪成功，返回生成的bitmap句柄，-1表示失败
 */
int32 clipBitmap(int32 b, int32 x, int32 y, int32 w, int32 h);

/**
 * 将bitmap绘制到屏幕缓存上
 * @param b bitmap句柄
 * @param x 绘制到屏幕上的x坐标
 * @param y 绘制到屏幕上的y坐标
 */
void drawBitmap(int32 b, int32 x, int32 y);

/**
 * 将bitmap上(tx,ty,w,h)区域绘制到屏幕上
 * @param x 绘制到屏幕上的x坐标
 * @param y 绘制到屏幕上的y坐标
 * @param w 绘制宽度
 * @param h 绘制高度
 * @param tx 裁剪区域x坐标
 * @param ty 裁剪区域y坐标
 */
void drawBitmapFlip(int32 b, int x, int y, int w, int h, int tx, int ty);

/**
 * 将bitmap上(tx,ty,tw,th)区域缩放绘制到屏幕(x,y,w,h)区域上
 * @param x 绘制到屏幕上的x坐标
 * @param y 绘制到屏幕上的y坐标
 * @param w 绘制宽度
 * @param h 绘制高度
 * @param tx
 * @param ty
 * @param tw
 * @param th 裁剪区域
 */
void drawBitmapEx(int32 b, int x, int y, int w, int h, int tx, int ty, int tw, int th);

/**
 * 将bitmap旋转绘制到屏幕上，并可指定绘制的透明度
 * @param b bitmap句柄
 * @param scrx,scry 绘制到屏幕上的中心位置
 * @param bx, by 图片旋转中心(相对于图片的左上角坐标)
 * @param r 旋转角度(顺时针)
 * @param alpha 绘制的不透明度(0~255)
 */
void drawBitmapRotate(int32 b, int scrx, int scry, int bx, int by, int r, int color);

/**
 * 设置显示区域，即设置裁剪区。只对区域内的绘制生效。(drect dline dpoint函数将不起作用)
 * @param x 区域x坐标
 * @param y 区域y坐标
 * @param w 宽度
 * @param h 高度
 * @returns TRUE 成功 FALSE 失败
 */
int clipRect(int x, int y, int w, int h);

/**
 * 绘制一个矩形
 * @param x 矩形x坐标
 * @param y 矩形y坐标
 * @param w 矩形宽
 * @param h 矩形高
 * @param color 矩形颜色(ARGB颜色值)
 */
void drawRect(int x, int y, int w, int h, int32 color);

/**
 * 绘制一个圆
 * @param x 圆的x坐标
 * @param y 圆的y坐标
 * @param r 圆的半径
 * @param color 颜色值(ARGB格式)
 */
void drawCir(int x, int y, int r, int32 color);

/**
 * 将bitmap绘制到另一个bitmap上
 * 将buf中的bitmap图片，从(sx, sy)开始的
 * 宽高为w, h的区域，绘制到图片di从(x, y)开始的地方。
 * @param di 目标bitmap句柄
 * @param buf 指向保存的bitmap
 * @param w,h 欲绘制区域的宽高
 * @param x,y 欲绘制区域在图片di的起始位置
 * @param sx,sy 欲绘制区域在图片buf的起始位置
 * @returns 0表示成功，-1表示失败
 */
int32 drawBitmapOld(int di, int buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);

/**
 * 清理bitmap，释放内存
 * @param b bitmap句柄
 * @returns 0表示成功，-1表示失败
 */
int32 bitmapFree(int32 b);

/**
 * 获取bitmap信息到BITMAPINFO结构体
 * @returns 0表示成功，-1表示失败
 */
int bitmapGetInfo(int b, BITMAPINFO *info);

/**
 * 将bitmap保存为指定格式
 * @param b bitmap句柄
 * @param filename 保存的文件名
 * @param type 保存图片的类型，取值如下：
 * 	_JPG jpg格式
 * 	_PNG png格式
 * 	_BMP16 bmp格式(16位图)
 * @param load 若保存的是jpg格式，将指定jpg的压缩质量，值越大质量越好
 * @returns 0表示成功，-1表示失败
 */
int32 saveBitmap(int32 b, char *filename, int type, int load);
