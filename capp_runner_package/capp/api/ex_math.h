/**
 * 手机c绘图相关接口
 */

/**
 * 检测点与矩形是否发生碰撞
 * @param x 点的x坐标
 * @param y 点的y坐标
 * @param rectx 矩形x坐标
 * @param recty 矩形y坐标
 * @param rectw 矩形宽度
 * @param recth 矩形高度
 * @returns TRUE表示发生碰撞，FALSE表示没有发生碰撞
 */
int isPointCollRect(int x, int y, int rectx, int recty, int rectw, int recth);

/**
 * 圆与矩形的碰撞检测
 * @param cx 圆心x坐标
 * @param cy 圆心y坐标
 * @param r 圆半径
 * @param rectx 矩形x坐标
 * @param recty 矩形y坐标
 * @param rectw 矩形宽度
 * @param recth 矩形高度
 * @returns TRUE表示发生碰撞，FALSE表示没有发生碰撞
 */
int isCirCollRect(int cx, int cy, int r, int rectx, int recty, int rectw, int recth);

/**
 * 矩形碰撞检测(做游戏常用的检测算法)
 * @param x1 矩形1的x坐标
 * @param x1 矩形1的y坐标
 * @param x1 矩形1宽度
 * @param x1 矩形1高度
 * @param x1 矩形2的x坐标
 * @param x1 矩形2的y坐标
 * @param x1 矩形2宽度
 * @param x1 矩形2高度
 * @returns TRUE表示发生碰撞，FALSE表示没有发生碰撞
 */
int isCollRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

/**
 * 求线段的长度(两点之间距离) 可用于计算圆与圆的碰撞(当两个圆的圆心距离小于它们的半径之和，那么碰撞成功)
 * @param x1 线段起点x坐标
 * @param y1 线段起点y坐标
 * @param x2 线段终点x坐标
 * @param y2 线段终点y坐标
 * @returns 线段的长度
 */
int getLineSize(int x1, int y1, int x2, int y2);

/**
 * 获得点(x2,y2)相对于点(x1,y1)的弧度值，取值(0~360)
 * @param x1 参考点x坐标
 * @param y1 参考点y坐标
 * @param x2 点的x坐标
 * @param y2 点的y坐标
 * @returns 0~360
 */
int getRadiam(int x1, int y1, int x2, int y2);

// 点(x,y)绕(px,py)旋转指定弧度r，得到旋转后的坐标
// 参数：旋转中心点(px,py)，旋转横向半径rx，旋转纵向半径ry， 旋转弧度r, 旋转后坐标指针(*x,*y)

/**
 * 点(x,y)绕(px,py)旋转指定弧度r，得到旋转后的坐标
 * @param px 旋转中心点的x坐标
 * @param py 旋转中心点的x坐标
 * @param rx 旋转横向半径
 * @param ry 旋转纵向半径
 * @param r 旋转弧度
 * @param x 旋转后x坐标指针
 * @param y 旋转后y坐标指针
 */
void toSpin(int px, int py, int rx, int ry, int r, int *x, int *y);
