#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"screenshotthread.h"
#include<QThread>
#include<QPainter>
#include <QImage>

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
    void Recyclet1();
    void RecvOneFrame(QImage oneFram);
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    screenshotThread *screenShot;
    QThread *t1;
    QImage mImage;
};
#endif // WIDGET_H
