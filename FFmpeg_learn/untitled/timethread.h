#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QObject>
#include<QTimer>
#include<QDebug>


class timeThread : public QObject
{
    Q_OBJECT
public:
    explicit timeThread(QObject *parent = nullptr);

    void knowNowTime();
    void startTimers();
signals:
     void Nowtime(const QString &timeStr);
private:
    QTimer *timer;
};

#endif // TIMETHREAD_H
