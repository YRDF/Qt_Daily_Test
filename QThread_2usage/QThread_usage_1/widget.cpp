#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建子线程对象
    Thread1 *t1gen = new Thread1();
    Bubble *bubble = new Bubble();

    connect(this,&Widget::sendNumToSon,t1gen,&Thread1::recvNum);

    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        qDebug()<<"使用子线程Thread1生成随机数!";
        emit sendNumToSon(f_num);
        //启动子线程
        t1gen->start();
    });
    connect(t1gen,&Thread1::genFinish,this,&Widget::recvVec);

    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        qDebug()<<"使用子线程bubble排序随机数!";
        emit sendVecToBubble(mainVec);
        //启动bubble排序线程
        bubble->start();
    });

    connect(this,&Widget::sendVecToBubble,bubble,&Bubble::recvVeced);

    connect(bubble,&Bubble::bbFinish,this,&Widget::recvBB);

    qDebug()<<"GUI thread = "<<QThread::currentThreadId();




}

Widget::~Widget()
{
    delete ui;
}

void Widget::recvVec(QVector<int> recQV)
{
    mainVec = recQV;
    for(int i = 0 ;i<f_num;i++){
        ui->textEdit->append(QString::number(recQV.at(i)));
    }
}

void Widget::recvBB(QVector<int> OutVec)
{
    BBoutVec = OutVec;
    for(int i = 0 ;i<f_num;i++){
        ui->textEdit_2->append(QString::number(BBoutVec.at(i)));
    }
}
