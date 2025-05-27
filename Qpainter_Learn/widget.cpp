#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);
    // painter.setPen(Qt::blue);

    //画笔抗锯齿
    // painter.setRenderHint(QPainter::Antialiasing,true);
    //画文字
    //画线
    //painter.drawLine(100,100,500,500);
    //画矩形
    // QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    // painter.drawRect(rectangle);
    //画椭圆，圆形
    // QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    // painter.drawEllipse(rectangle);
    //在矩形中画弧
    // QRectF rectangle(200,200,200,200);
    // painter.drawArc(rectangle,180*16,-180*16);
    // painter.drawArc(rectangle,-180*16,180*16);
    //在矩形中画扇形
    // QRectF rectangle(200,200,200,200);
    // painter.drawPie(rectangle,0*16,180*16);
    //painter.drawRect(rectangle);
    //画刷刷满整个widget
    /*painter.setBrush(Qt::black);
    painter.setFont(QFont("Arial", 30));

    painter.drawText(rect(), Qt::AlignCenter, "Qt");

    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    painter.drawArc(rect(), startAngle, spanAngle);
    painter.drawRect(rect());
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
    qDebug()<<"wight is : "<<rect().width();
    qDebug()<<"height is : "<<rect().height();
    painter.drawText(100,100,100,100,Qt::AlignCenter,"Qt");
    painter.drawText(0,30,"我是人");*/


    //线性渐变  通过画刷
    // QPainter painter(this);
    // painter.setPen(Qt::yellow);
    // QRectF rectangle(200,200,200,200);
    // painter.drawRect(rectangle);

    // //渐变色
    // QLinearGradient lineGradient(200,200,400,400);
    // lineGradient.setColorAt(0.1,Qt::white);
    // // lineGradient.setColorAt(0.3,Qt::black);
    // // lineGradient.setColorAt(0.3,Qt::white);
    // lineGradient.setColorAt(1,Qt::black);

    // QBrush brush(lineGradient);
    // painter.setBrush(brush);
    // painter.setPen(Qt::NoPen); // 禁用边框
    // painter.drawRect(rectangle);


    //径向渐变
    // QPainter painter(this);
    // painter.setPen(Qt::yellow);
    // QRectF rectangle(200,200,200,200);
    // painter.drawRect(rectangle);

    // QRadialGradient radialGradient(300,300,100);
    // radialGradient.setColorAt(0.1,Qt::white);
    // radialGradient.setColorAt(1,Qt::black);

    // QBrush brush(radialGradient);
    // painter.setPen(Qt::NoPen);
    // painter.setBrush(brush);
    // painter.drawRect(rectangle);

    //圆锥渐变
    // QPainter painter(this);
    // painter.setPen(Qt::yellow);
    // QRectF rectangle(200,200,200,200);
    // painter.drawRect(rectangle);

    // QConicalGradient conicalGradient(300,300,100);
    // conicalGradient.setColorAt(0.1,Qt::white);
    // conicalGradient.setColorAt(1,Qt::black);

    // QBrush brush(conicalGradient);
    // painter.setPen(Qt::NoPen);
    // painter.setBrush(brush);
    // painter.drawRect(rectangle);

    //坐标转移

}
