#include "widget.h"
#include "ui_widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,[this](){
        unsigned version = avcodec_version();
        unsigned major = (version >> 16) & 0xFF; // 主版本
        unsigned minor = (version >> 8) & 0xFF;  // 次版本
        unsigned patch = version & 0xFF;         // 补丁版本
        QString QVs = QString("%1.%2.%3").arg(major).arg(minor).arg(patch);
        qDebug()<<"version is: "<<QVs;
        ui->label->setText(QVs);
    });
}

Widget::~Widget()
{
    delete ui;
}
