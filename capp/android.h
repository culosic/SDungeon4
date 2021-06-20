/**
 * Android手机控件、功能相关接口。
 */

#include <base.h>

// 控件event事件的类型
enum
{
	VIEW_DOWN = 20, // 控件被按下
	VIEW_UP = 21	// 控件被释放
};

// view的显示方式
enum
{
	VISIBLE = 0,   // 显示
	INVISIBLE = 4, // 不显示，但占用屏幕空间
	GONE = 8	   // 不显示，并不占用屏幕空间
};

// toast的显示类型
enum
{
	LENGTH_SHORT, // 短时间显示
	LENGTH_LONG	  // 长时间显示
};

/**
 * 运行Linux命令
 * @param text 命令文本
 * @returns 0表示成功，-1表示失败
 */
int cmd(char *text);

/**
 * 以root方式运行Linux命令，此函数须确保手机已root，请谨慎使用此函数，若使用不当造成的任何后果与作者无关。
 * @param text Linux命令
 * @returns 0表示成功，-1表示失败
 */
int rootcmd(char *text);

/**
 * 显示Toast
 * @param text 要显示的文本
 * @param type 显示方式。`LENGTH_SHORT`表示短时间显示，`LENGTH_LONG`表示长时间显示
 * @returns 0表示成功，-1表示失败
 */
void toast(char *text, int type);

/**
 * 获取data目录
 * @param datafile data目录下文件夹名称
 * @returns data目录下datafile的绝对路径(不需要手动释放内存)
 */
char *getDataPath(char *datafile);

/**
 * 从assets目录读取文件。
 * 注意：读取的文件必须严格区分大小写，否则运行apk将找不到文件
 * @param filename 读取的文件名
 * @param len 读取成功后，len的内容为读取的文件长度，若读取失败，len的内容为0
 * @returns 读取的数据缓存
 */
void *readFileFromAssets(char *filename, int *len);

/**
 * 设置程序标题名
 * @param text 待设置的标题名
 */
void setTitle(char *text);

/**
 * 从assets目录加载xml布局文件
 */
void setContextView(char *filename);

/**
 * 创建一个view控件，返回控件句柄
 * @param name 控件名称
 */
int createView(char *name);

/**
 * 清除屏幕上所有控件
 */
void clearView();

/**
 * 设置屏幕显示方式
 */
void setOrientation(int orien);

/**
 * 创建一个view控件，返回控件句柄
 * @param view 控件的句柄
 * @param words 属性字符串
 */
void setView(int view, char *words);

/**
 * 通过id找到view
 * @param id view的id
 * @returns view的句柄
 */
int findViewById(int id);

/**
 * 获取View控件id
 * @param view View控件句柄
 * @returns view的id
 */
int view_getId(int view);

/**
 * 添加一个控件
 * @param layout 父控件句柄
 * @param view 要添加的view句柄
 */
void addView(int layout, int view);

/**
 * 设置view的显示方式
 * @param view 控件的句柄
 * @param visibility 显示方式。`VISIBLE`表示显示；`INVISIBLE`表示不显示，但占用屏幕空间；`GONE`表示不显示，并不占用屏幕空间。
 */
void setVisibility(int view, int visibility);

/**
 * 设置View的背景图片
 * @param view View控件句柄
 * @param bitmap 背景bitmap图片(需要在你的程序中包含graphics.h头文件)
 */
void view_setBackground(int view, int bitmap);

/**
 * 获取view的文本(对TextView EditView Button有效)
 * @param view 控件句柄
 * @returns 文本(unicode编码)，返回的文本需要用free函数进行手动释放
 */
char *view_getText(int view);

/**
 * 设置view的文本
 * @param view 控件句柄
 * @param text 要设置的文本(unicode编码)
 */
void view_setText(int view, char *text);

/**
 * 关闭输入法
 */
void closeInput();

/**
 * EditText光标跳转到指定位置
 * @param edit EditText句柄
 * @param start 光标位置
 */
void edit_goto(int edit, int start);

/**
 * EditText光标选择
 * @param edit EditText句柄
 * @param start 光标开始位置
 * @param end 光标结束位置
 */
void edit_selection(int edit, int start, int end);

/**
 * 向EditText中插入文本
 * @param edit EditText句柄
 * @param start 要插入的位置
 * @param text 文本
 */
void edit_insert(int edit, int start, char *text);

/**
 * 设置WebView的url
 * @param view WebView控件句柄
 * @param url 待设置的url(gb2312编码)
 */
void loadUrl(int view, char *url);

/**
 * 设置VideoView的播放文件路径
 * @param filename 视频文件名
 */
void setVideoPath(char *filename);

/**
 * VideoView开始播放
 * 当VideoView播放完成后，将发送event事件event(32,0,0);
 * @param id View控件id
 */
void videoStart(int id);

/**
 * VideoView暂停播放
 * @param id View控件id
 */
void videoPause(int id);

/**
 * VideoView跳转到指定时间
 * @param id View控件句柄
 * @param time 播放时间(单位：ms)
 */
void videoSeekTo(int id, int time);

/**
 * 获取seekBar的进度值
 * @param view seekBar控件句柄
 */
int seekBar_getProgress(int view);

/**
 * 设置seekBar的进度值
 * @param view seekBar控件句柄
 * @param progress 进度值
 */
void seekBar_setProgress(int view, int progress);

/**
 * 设置seekBar的最大值
 * @param view seekBar句柄
 * @param max 最大值
 */
void seekBar_setMax(int view, int max);

// 当SeekBar的进度条被用户改变，将发送event事件
// 参数：
// id SeekBar的id
// progress SeekBar的进度值

// 当SeekBar进度改变时
// event(23,id,progress);

// SeekBar滑动开始
// event(24,id,0);

// SeekBar滑动结束
// event(25,id,0);

/**
 * 获取输入法类型
 */
int inputMode();

/**
 * 设置系统剪切板内容
 * @param text 待设置的内容(unicode编码)
 */
void clipSetText(char *text);

/**
 * 获取系统剪切板内容
 * @returns 系统剪切板文本(unicode编码)
 */
char *clipGetText();

/**
 * 在ListView中添加一项
 * @param view ListView控件句柄
 * @param pos 添加位置
 * @param bitmap 预添加的列表项的图标(bitmap句柄，需要在你的代码中包含头文件graphics.h)
 * @param title 预添加的列表项标题
 * @param info 预添加的列表项内容
 */
void list_add(int view, int pos, int bitmap, char *title, char *info);

/**
 * 在ListView中删除一项
 * @param view ListView控件句柄
 * @param pos 删除选项的位置
 */
void list_remove(int view, int pos);

// 当ListView被点击，将发送event事件
// 参数：
// id listView的id
// pos 点击项的位置
// event(19,id,pos);

/**
 * 获取ListView的长度
 * @param view ListView控件句柄
 * @returns ListView的长度
 */
int list_getSize(int view);

/**
 * 获取ListView标题
 * @param view ListView控件句柄
 * @param pos 预获取的标题位置
 * @returns ListView在pos位置的标题(unicode编码)
 */
char *list_getItemTitle(int, int);

/**
 * 获取ListView内容
 * @param view ListView控件句柄
 * @param pos 预获取的位置
 * @returns ListView在pos位置的内容(unicode编码)
 */
char *list_getItemInfo(int view, int pos);

/**
 * 刷新ListView
 * @param view ListView控件句柄
 */
void list_notifyData(int view);

/**
 * 创建Intent。
 * 注：Intent是安卓的消息事件接口
 * @returns Intent句柄
 */
int in_createIntent();

/**
 * 设置Intent动作
 * @param intent Intent句柄
 * @param action 待设置的动作字符串
 */
void in_setAction(int intent, char *action);

/**
 * 设置Intent数据
 * @param intent Intent句柄
 * @param data 待设置的字符串数据
 */
void in_setData(int intent, char *data);

/**
 * 设置Intent类型
 * @param intent Intent句柄
 * @param type 待设置的字符串类型
 */
void in_setType(int intent, char *type);

/**
 * 为Intent设置发送的数据
 * @param intent Intent句柄
 * @param name 数据名称
 * @param data 字符串数据
 */
void in_putEx(int intent, char *name, char *data);

/**
 * 通过Intent启动相关的activity。
 * 如果只有一个Activity符合要求，安卓系统会立即启动这个Activity；
 * 如果有多个符合要求，安卓系统会显示符合要求的程序列表。
 * @param intent Intent句柄
 */
void startActivity(int intent);
