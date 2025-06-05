#ifndef THREAD1_H
#define THREAD1_H

#include <QThread>
#include<QDebug>
#include<QVector>
#include<QRandomGenerator>
#include<QElapsedTimer>

class Thread1 : public QThread
{
    Q_OBJECT
public:
    explicit Thread1(QObject *parent = nullptr);
protected:
    void run()override;

public slots:
    void recvNum(int num);
signals:
    void genFinish(QVector<int>);
private:
    QVector<int> randnum;
    int m_num;
};

//冒泡排序
class Bubble : public QThread
{
    Q_OBJECT
public:
    explicit Bubble(QObject *parent = nullptr);
protected:
    void run()override;

public slots:
    void recvVeced(QVector<int> mainVec);
signals:
    void bbFinish(QVector<int>);
private:
    QVector<int> bbRecv;
};


#endif // THREAD1_H
