#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(359,598);
    setWindowFlag(Qt::FramelessWindowHint);

    menuQuit = new QMenu(this);
    menuQuit->setStyleSheet("QMenu::item {color:pink;border-radius:7px}");
    QAction *closeAct = new QAction(QIcon(":/res/close.png"),tr("退出"),this);
    menuQuit->addAction(closeAct);

    connect(menuQuit,&QMenu::triggered,this,[=](){
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        //qDebug()<<"right mouse button clicked";
        menuQuit->exec(QCursor::pos());
    }
    if(event->button() == Qt::LeftButton){
        //qDebug()<<"left mouse button clicked";
        //鼠标当前位置
        // qDebug()<<event->globalPosition();
        //窗口当前位置
        // qDebug()<<this->pos();
        movepoint = this->pos()-event->globalPosition();
        //qDebug()<<movepoint;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move((event->globalPosition()+movepoint).toPoint());
}
