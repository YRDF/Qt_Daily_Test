#include "thread2.h"



Thread2::Thread2(QObject *parent)
    : QObject{parent}
{}

void Thread2::generateNum(int num)
{
    qDebug()<<"子线程启动"<<QThread::currentThreadId();
    generateVec.clear();
    genNum = num;
    //记录使用时间
    QElapsedTimer time;
    time.start();
    //在该线程生成随机数
    for(int i = 0 ;i<genNum;i++){
        int randomInt = QRandomGenerator::global()->bounded(500000); // 生成0到500000之间的整数（包含0和500000）
        generateVec.emplaceBack(randomInt);
    }
    emit genFinish(generateVec);
    int totaltime = time.elapsed();
    qDebug()<<"子线程生成"<<genNum<<"个数字共使用了"<<totaltime<<"毫秒";
}


Bubble::Bubble(QObject *parent): QObject{parent}
{
}

void Bubble::sortNum(QVector<int> recVec)
{
    qDebug()<<"冒泡排序线程的线程id为: "<<QThread::currentThreadId();
    //记录使用时间
    QElapsedTimer time;
    time.start();
    sendVec = recVec;
    int temp = 0;
    for(int i=0;i<sendVec.size();i++){
        for(int j = 0;j<sendVec.size()-i-1;j++){
            if(sendVec[j]>sendVec[j+1]){
                temp = sendVec[j];
                sendVec[j] = sendVec[j+1];
                sendVec[j+1] = temp;
            }
        }
    }
    emit sortFinish(sendVec);
    int totaltime = time.elapsed();
    qDebug()<<"子线程冒泡排序共使用了"<<totaltime<<"毫秒";
}
