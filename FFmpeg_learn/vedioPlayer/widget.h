#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"screenshotthread.h"
#include<QThread>

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

private:
    Ui::Widget *ui;
    screenshotThread *screenShot;
    QThread *t1;
};
#endif // WIDGET_H
