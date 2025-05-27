#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QObject::connect(ui->ShowBtn,&QPushButton::clicked,this,&Widget::ShowBtn_Clicked);
    QObject::connect(ui->ClearBtn,&QPushButton::clicked,this,&Widget::ClearBtn_Clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ShowBtn_Clicked()
{
    ui->textEdit->append("hello world!");
}

void Widget::ClearBtn_Clicked()
{
    ui->textEdit->clear();
}
