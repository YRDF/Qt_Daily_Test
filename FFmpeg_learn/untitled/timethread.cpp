#include "timethread.h"

#include <QThread>
#include <QTime>

timeThread::timeThread(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &timeThread::knowNowTime);
}

// 添加启动方法
void timeThread::startTimers()
{
    timer->start(500); // 在目标线程中启动
}

void timeThread::knowNowTime()
{
    QTime currentTime = QTime::currentTime();  // 获取当前时间
    qDebug()<<"现在是： "<<currentTime<<QThread::currentThreadId();
    emit Nowtime(currentTime.toString());
}
