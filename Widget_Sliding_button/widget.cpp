#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mybtn = new MySlidBtn(this);
    mybtn->setFixedSize(600,200);
    mybtn->move(100,100);
    connect(mybtn,&MySlidBtn::isClicked,this,[](){
        qDebug()<<"mybtn is clicked!";
    });
    connect(mybtn,&MySlidBtn::isClickedWithParams,this,[](bool value){
        qDebug()<<value;
    });
}

Widget::~Widget()
{
    delete ui;
}
