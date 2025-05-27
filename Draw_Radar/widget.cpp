#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPainter painter(this);
    painter.setPen(Qt::green,3);

}

Widget::~Widget()
{
    delete ui;
}
