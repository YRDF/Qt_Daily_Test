#include "thread1.h"



Thread1::Thread1(QObject *parent):QThread(parent)
{
}

void Thread1::run()
{
    qDebug()<<"子线程的线程id为: "<<QThread::currentThreadId();

    //记录使用时间
    QElapsedTimer time;
    time.start();
    //在该线程生成随机数
    for(int i = 0 ;i<m_num;i++){
        int randomInt = QRandomGenerator::global()->bounded(500000); // 生成0到500000之间的整数（包含0和500000）
        randnum.emplaceBack(randomInt);
    }
    emit genFinish(randnum);
    int totaltime = time.elapsed();
    qDebug()<<"子线程生成"<<m_num<<"个数字共使用了"<<totaltime<<"毫秒";
}

void Thread1::recvNum(int num)
{
    m_num = num;
}

Bubble::Bubble(QObject *parent):QThread(parent)
{
}

void Bubble::run()
{
    qDebug()<<"子线程的线程id为: "<<QThread::currentThreadId();
    //记录使用时间
    QElapsedTimer time;
    time.start();
    int temp;
    for(int i=0;i<bbRecv.size();++i){
        for(int j =0;j<bbRecv.size()-i-1;++j){
            if(bbRecv[j]>bbRecv[j+1]){
                temp = bbRecv[j];
                bbRecv[j] = bbRecv[j+1];
                bbRecv[j+1] = temp;
            }
        }
    }
    emit bbFinish(bbRecv);
    int totaltime = time.elapsed();
    qDebug()<<"子线程冒泡排序共使用了"<<totaltime<<"毫秒";
}

void Bubble::recvVeced(QVector<int>mainVec)
{
    bbRecv = mainVec;
}


