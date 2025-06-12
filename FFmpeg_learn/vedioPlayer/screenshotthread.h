#ifndef SCREENSHOTTHREAD_H
#define SCREENSHOTTHREAD_H

#include <QObject>
//qt的转换方法，转为png
#include <QImage> // 添加 Qt 图像处理头文件

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
}

class screenshotThread : public QObject
{
    Q_OBJECT
public:
    explicit screenshotThread(QObject *parent = nullptr);
    int screenShot();
    // 使用Qt保存帧为PNG
    void SaveFrameWithQt(AVFrame *frame, int width, int height, int index);
    ~screenshotThread();
private:
    const char *file_path = "E:/cpp_test/movie_res/r_and_m.mp4";

    AVFormatContext *pFormatCtx = NULL;         //用于存储音视频文件的格式上下文信息。
    AVCodecContext *pCodecCtx = NULL;           //用于存储编解码器上下文信息。
    const AVCodec *pCodec = NULL;               //指向一个编解码器。
    AVFrame *pFrame = NULL, *pFrameRGB = NULL;  //用于存储解码后的帧数据。
    AVPacket *pPacket = NULL;                   //用于存储音视频数据包。
    struct SwsContext *sws_ctx = NULL;          //用于图像格式转换的上下文
    uint8_t *buffer = nullptr;

    int videoStream = -1;
    int ret = 0;
    int frame_count = 0;

signals:
    void screenShootFinish(); // 完成截图进行清除
    void sig_GetOneFrame(QImage); //每获取到一帧图像，就发送此信号
};

#endif // SCREENSHOTTHREAD_H
