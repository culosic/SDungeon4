/**
 * 游戏开发（精灵）
 */

//创建照相机
/*
参数：
x 照相机视图相对于屏幕上的x坐标
y 照相机视图相对于屏幕上的y坐标
w 视图宽度(保留，该参数不起作用)
h 视图高度(保留，该参数不起作用)
返回值： 照相机句柄
*/
int ca_create(int x, int y, int w, int h);

//设置照相机的位置
/*
参数：
id 照相机句柄
x 照相机视图在屏幕上的x坐标
y 照相机视图在屏幕上的y坐标
返回值： 0成功 -1失败
*/
int ca_setxy(int id, int x, int y);

//获取照相机在屏幕上的x坐标
/*
参数：
id 照相机句柄
返回值：照相机x坐标
*/
int ca_getx(int id);

//获取照相机在屏幕上的y坐标
/*
参数：
id 照相机句柄
返回值：照相机在屏幕上的y坐标
*/
int ca_gety(int id);

//照相机移动
/*
参数：
id 照相机句柄
movex 横向移动距离
movey 纵向移动距离
返回值：0成功 -1失败
*/
int ca_move(int id, int movex, int movey);

//销毁照相机
/*
参数：
id 照相机句柄
返回值：0成功 -1失败
*/
int ca_free(int id);

//从assets目录读取精灵文件
/*
参数：
filename 精灵文件名
bitmap 精灵bitmap图片
返回值：
>0精灵句柄
0 读取失败
*/

int sp_read(char *filename, int bitmap);

//设置精灵显示/隐藏
/*
参数：
id 精灵句柄
isdraw 显示/隐藏(TRUE/FALSE)
*/

int sp_setDraw(int id, int isdraw);

//获取精灵状态(显示/隐藏)
/*
参数：
id 精灵句柄
返回值：显示/隐藏(TRUE/FALSE)
*/

int sp_isDraw(int id);

//获取精灵id
/*
参数：
id 精灵句柄
返回值：精灵id
*/
int sp_getId(int id);

//复制一个精灵
/*
参数：
id 要复制的精灵句柄
返回值：复制精灵句柄
*/

int sp_copy(int id);

//设置精灵的动作
/*
参数：精灵句柄，动作id
返回值： 成功(0) 失败(-1)
*/
int sp_setAction(int id, int ac_id);

//精灵移动
/*
参数：
id 精灵句柄
movex 横向移动距离
movey 纵向移动距离
返回值： 成功(0) 失败(-1)
*/

int sp_move(int id, int movex, int movey);

//得到当前图像的帧序号
/*
参数：
id 精灵句柄
返回值：帧序号
*/
int sp_getFrame(int id);

//获取精灵的动作
/*
参数：
id 精灵句柄
返回值：精灵动作id
*/

int sp_getAction(int id);

//设置精灵坐标
/*
参数：
id 精灵句柄
x 待设置的x坐标
y 待设置的y坐标
返回值：成功(0) 失败(-1)
*/

int sp_setxy(int id, int x, int y);

//获取精灵x坐标
/*
返回值：精灵的x坐标
*/

int sp_getx(int id);

//获取精灵y坐标
/*
返回值：精灵的y坐标
*/

int sp_gety(int id);

//获取精灵宽度 参数：精灵句柄
/*
参数：
id 精灵句柄
返回值：精灵的宽度
*/
int sp_getWidth(int id);

//获取精灵高度 参数：精灵句柄
/*
参数：
id 精灵句柄
返回值：精灵的高度
*/
int sp_getHeight(int id);

//精灵是否被x y点中
/*
参数：
id 精灵句柄
x x坐标
y y坐标
返回值：被点中(TRUE) 没有被点中(FALSE)
*/
int sp_impact(int id, int x, int y);

//精灵碰撞事件
//参数：精灵1 精灵2
//返回值：碰撞成功(TRUE) 碰撞失败(FALSE)
int sp_crash(int id1, int id2);

//显示精灵
/*
参数：
id 精灵句柄
camera 照相机句柄
返回值：成功(0) 失败(-1)
*/

int sp_draw(int id, int camera);

//精灵运动逻辑，每调用一次此函数，精灵的当前动作就会跳转到下一帧
/*
参数：
id 精灵句柄
*/

void sp_run(int id);

//销毁精灵
/*
参数：
id 精灵句柄
返回值： 成功(0) 失败(-1)
*/

int sp_free(int id);

//创建世界
/*

返回值：
>0 世界句柄
<=0 创建失败
*/

int world_create();

//在世界中添加精灵
/*
参数：
id 世界句柄
sprite 精灵句柄
返回值： 成功(0) 失败(-1)
*/

int world_addSprite(int id, int sprite);

//从世界中删除一个精灵
/*
参数：
id 世界句柄
sprite 精灵句柄

返回值： 0成功 -1失败
*/
int world_removeSprite(int id, int sprite);

//设置世界的照相机
/*
参数：
id 世界句柄
camera 待设置的照相机句柄
返回值： 成功(0) 失败(-1)
*/

int world_setCamera(int id, int camera);

/*
排列世界中的精灵，使其按指定方式显示，用于生成2.5D画面
参数：
id 世界句柄
type 取值如下
1 左上角视图
2 左下角视图
3 右上角视图
4 右下角视图
返回值： 成功(0) 失败(-1)
*/
int world_rank(int id, int type);

//显示世界
/*
参数：
id 世界句柄
返回值： 成功(0) 失败(-1)
*/

int world_draw(int id);

//世界逻辑
/*
参数：
id 世界句柄
返回值： 成功(0) 失败(-1)
*/

int world_run(int id);

//销毁世界
//销毁世界并不会销毁摄像机，精灵，它们需要单独销毁
/*
参数：
id 世界句柄
返回值：成功(0) 失败(-1)
*/
int world_free(int id);
