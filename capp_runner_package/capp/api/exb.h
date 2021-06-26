/**
 * 手机c文件浏览器接口
 */

#include <base.h>

/**
 * 初始化手机c文件浏览器
 * @param type 文件浏览器类型，取值如下：
 *	0 普通模式
 *	1 只浏览文件
 *	2 只浏览文件夹
 * @returns 0表示成功，-1表示失败
 */
int fv_init(int type);

/**
 * 设置浏览文件类型
 * @param text 文件类型
 * @param isView 是否显示(TRUE / FALSE)。
 *	例如，只显示mp3、mp4文件：fv_settype(".mp3|.mp4",TRUE);
 */
int fv_settype(char *text, int isView);

/**
 * 开始显示文件列表
 * @param path 要获取的文件路径
 * @returns 0表示成功，-1表示失败
 */
int fv_begin(char *path);

/**
 * 获取手机c文件浏览器路径(获取的路径不需要释放，使用fv_end()函数统一释放内存)
 * @returns 相对于平台路径
 */
char *fv_getpath();

// 文件浏览器event事件
// event(int type=10,p1=DLG_OK,0);// 文件浏览器确定键被点击
// event(int type=10,p1=DLG_CANCEL,0);// 文件浏览器取消键被点击

/**
 * 结束文件浏览
 * @returns 0表示文件浏览器释放成功，-1表示释放失败
 */
int fv_end();

/**
 * 设置虚拟键盘类型
 * @param type 取值如下：
 * 	0 没有任何按键
 * 	1 全部按键
 * 	2 游戏键盘
 * 	3 只有方向键 确定键 返回键
 */
void setpadtype(int type);

/**
 * 检测虚拟键盘上某个键是否被按下
 * @param key 按键键值
 * @returns 0表示检测成功(按键正在被按下)，-1表示释放失败
 */
int getkeypressed(int32 key);

/**
 * 设置字体大小
 * @param font 字号
 * @param size 待设置的大小
 */
void setTextSize(int font, int size);

/**
 * 解压zip。
 * 解压成功后，将发送event事件 event(30,0,0); 
 * 解压失败将发送 event(30,-1,0); 
 * @param filename 要解压的文件名
 * @param path 解压后文件存放路径
 */
void unZip(char *filename, char *path);

/**
 * 打开传感器
 */
int sensorOn();

/**
 * 打开传感器。
 * 注：传感器的支持程度和手机有关，部分手机可能只支持加速度传感器。
 * @param sensor 传感器类型，取值如下：
 * 	1 加速度传感器
 * 	2 磁力计
 * 	3 倾角事件
 * 	4 陀螺仪
 * 	5 光线传感器
 * 	6 距离传感器
 * 	7 温度传感器
 * @returns 0表示成功，-1表示失败
 */
int sensorStart(int sensor);

// 传感器event事件

// 当成功监听传感器后，传感器将发送event事件
// event(int type=18,int sensor,(int)(&MOTION_ACC));
// 其中，最后一个参数为结构体MOTION_ACC，定义如下
// typedef struct
// {
// int32 x;
// int32 y;
// int32 z;
// } MOTION_ACC;

/**
 * 停止传感器事件
 * @returns 0表示成功，-1表示失败
 */
int sensorStop();

/**
 * 关闭传感器
 * @returns 0表示成功，-1表示失败
 */
int sensorOff();

/**
 * 文本编码转换
 * @param length 要转换的文本的长度
 * @param text 要转换的文本
 * @param coding 当前文本编码
 * @param tocoding 转换后的文本编码
 * @returns 转换后的文本
 */
char *ex_coding(int length, char *text, char *coding, char *tocoding);
