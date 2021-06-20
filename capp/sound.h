/***
 * 手机c音频相关接口
 */

#include <base.h>

// 音频播放位置相关。
typedef struct
{
	int32 pos; // 音频播放位置的指针
} T_DSM_AUDIO_POS;

/**
 * 设备初始化 每次播放前需调用
 * @param type 播放设备类型。0-4，总共支持5个设备
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 soundinit(int32 type);

/**
 * 加载音频文件
 * @param type 设备类型
 * @param filename 数据文件名称，相对路径，GB编码，这里注意的是从apk外部读取文件
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 soundloadfile(int32 type, char *filename);

/**
 * 播放音频文件
 * @param type 设备类型
 * @param block 1：阻塞式向底层发送播放请求；0：非阻塞凡是向底层发送播放请求
 * @param loop 0：单次播放；1：循环播放；2：nes pcm 播放方式
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 soundplay(int32 type, int32 block, int32 loop);

/**
 * 暂停播放音频文件
 * @param type 设备类型
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 soundpause(int32 type);

/**
 * 继续播放音频文件
 * @param type 设备类型
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */

int32 soundresume(int32 type);
/**
 * 停止播放音频文件
 * @param type 设备类型
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */

int32 soundstop(int32 type);
/**
 * 关闭设备
 * @param type 设备类型
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 soundclose(int32 type);
/**
 * 音量调节
 * @param volume 音量大小0~5
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 setvolume(int32 volume);

/**
 * 获取音乐的总时间秒S
 * 注：mtk上此接口在以文件形式播放的时候有效。
 * @param p 指向这个数据结构（T_DSM_AUDIO_POS）的指针的指针，这个数据结构的值就是总的时间
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 getsoundtotaltime(int32 type, uint8 **p);

/**
 * 获取当前已经播放的时间秒S
 * 注：mtk上此接口在以文件形式播放的时候有效。
 * @param p 指向这个数据结构（T_DSM_AUDIO_POS）的指针的指针，这个数据结构的值就是已经播放的时间
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */

int32 getsoundcurtime(int32 type, uint8 **p);

/**
 * 获取当前已经播放的时间毫秒ms。
 * 注：mtk上此接口在以文件形式播放的时候有效。
 * @param p 指向这个数据结构（T_DSM_AUDIO_POS）的指针的指针，这个数据结构的值就是已经播放的时间
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */

int32 getsoundcurtimems(int32 type, uint8 **p);

/**
 * 设置播放位置，相对文件或者缓冲的起始位置的偏移量
 * @param pos 相对文件或者缓冲的起始位置的偏移量
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 setplaypos(int32 type, T_DSM_AUDIO_POS *pos);

/**
 * 设置播放时间，相对文件或者缓冲的起始时间的偏移量
 * @param pos 相对文件或者缓冲的起始时间的偏移量，单位：ms
 * @returns 0表示初始化成功 -1表示失败 1表示不支持该功能
 */
int32 setplaytime(int32 type, T_DSM_AUDIO_POS *pos);

/**
 * 获取当前设备的状态
 * @returns 设备状态值。0表示成功 -1表示失败 1表示不支持该功能
 */
int32 getdevicestate(int32 type);