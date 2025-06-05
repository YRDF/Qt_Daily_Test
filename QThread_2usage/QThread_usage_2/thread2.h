#ifndef THREAD2_H
#define THREAD2_H

#include<QVector>
#include <QObject>
#include<QDebug>
#include <QThread>
#include<QRandomGenerator>
#include<QElapsedTimer>

class Thread2 : public QObject
{
    Q_OBJECT
public:
    explicit Thread2(QObject *parent = nullptr);

    void generateNum(int num);
signals:
    void genFinish(QVector<int>);
private:
    QVector<int> generateVec;
    int genNum;
};


//冒泡排序
class Bubble : public QObject
{
    Q_OBJECT
public:
    explicit Bubble(QObject *parent = nullptr);

    void sortNum(QVector<int> recVec);
signals:
    void sortFinish(QVector<int>);
private:
    QVector<int> sendVec;
};

#endif // THREAD2_H
