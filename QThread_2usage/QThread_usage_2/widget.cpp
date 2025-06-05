#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QThread *th2Use = new QThread();
    Thread2 *t2 = new Thread2();
    t2->moveToThread(th2Use);
    th2Use->start();

    qDebug()<<"主线程启动"<<QThread::currentThreadId();

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        emit sentNum(use_Num);
    });

    connect(this,&Widget::sentNum,t2,&Thread2::generateNum);

    connect(t2,&Thread2::genFinish,this,&Widget::randNumShow);


    //冒泡排序线程
    QThread *thBubble = new QThread();
    Bubble *bubble = new Bubble();
    bubble->moveToThread(thBubble);
    thBubble->start();
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        emit StarSort(ShowrandVec);
    });

    connect(this,&Widget::StarSort,bubble,&Bubble::sortNum);
    connect(bubble,&Bubble::sortFinish,this,&Widget::sortNumShow);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::randNumShow(QVector<int> TVec)
{
    ShowrandVec = TVec;
    ui->textEdit->clear();
    for(int i = 0 ;i<use_Num;i++){
        ui->textEdit->append(QString::number(ShowrandVec.at(i)));
    }
}

void Widget::sortNumShow(QVector<int> sortVec)
{
    ShowSortVec = sortVec;
    ui->textEdit_2->clear();
    for(int i = 0 ;i<use_Num;i++){
        ui->textEdit_2->append(QString::number(ShowSortVec.at(i)));
    }
}
