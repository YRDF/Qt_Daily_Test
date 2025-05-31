#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(361,597);
    setWindowFlag(Qt::FramelessWindowHint);
}

Widget::~Widget()
{
    delete ui;
}
