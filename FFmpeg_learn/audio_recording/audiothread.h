#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QObject>
#include<QFile>
#include<QDebug>
#include<QThread>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}
///由于我们建立的是C++的工程
///编译的时候使用的C++的编译器编译
///而FFMPEG是C的库
///因此这里需要加上extern "C"
///否则会提示各种未定义

class audiothread : public QObject
{
    Q_OBJECT
public:
    explicit audiothread(QObject *parent = nullptr);
    void setStopBool(bool b);
public slots:
    void audioOperater();
private:
    bool stopAuSon;
signals:
};

#endif // AUDIOTHREAD_H
