#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mybtn = new MySlidBtn(this);
    mybtn->setFixedSize(200,50);
    mybtn->move(100,100);
}

Widget::~Widget()
{
    delete ui;
}
