#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include<QThread>
#include"thread1.h"

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
signals:
    void sendNumToSon(int numfather);
    void sendVecToBubble(QVector<int> sendVec);
public slots:
    void recvVec(QVector<int> recQV);
    void recvBB(QVector<int> OutVec);
private:
    Ui::Widget *ui;
    int f_num = 5000;
    QVector<int> mainVec;
    QVector<int> BBoutVec;
};
#endif // WIDGET_H
