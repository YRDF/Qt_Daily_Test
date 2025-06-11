#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QFile>
#include<QDebug>
#include<QThread>
#include"audiothread.h"
#include"audioPlay.h"

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

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_audio_play_btn_clicked();

private:
    Ui::Widget *ui;
    bool stopRecoding = false;
    QThread *t1;
    QThread *t2;
    audiothread *ad;
    audioPlay * ap;
};
#endif // WIDGET_H
