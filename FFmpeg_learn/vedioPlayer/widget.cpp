#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    t1 = new QThread();
    screenShot = new screenshotThread();
    screenShot->moveToThread(t1);

    connect(t1,&QThread::started,screenShot,&screenshotThread::screenShot);
    t1->start();

}


Widget::~Widget()
{
    delete ui;
}
