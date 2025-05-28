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
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::black));
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(rect());
    //平移坐标
    painter.translate(rect().center());
    QRadialGradient radialGradient(0, 0, height()/2);
    // 设置颜色停靠点
    radialGradient.setColorAt(0.0, QColor(255,0,0,50)); // 中心颜色
    radialGradient.setColorAt(1.0, QColor(255,0,0,250));  // 外围颜色
    // 使用这个渐变创建 QBrush
    QBrush brush(radialGradient);
    painter.setBrush(brush);
    // 画大圆
    painter.drawEllipse(QPoint(0,0),height()/2,height()/2);
    painter.setBrush(Qt::NoBrush);
    // 画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),60,60);

    //旋转坐标轴
    //旋转一个刻度是多少度
    double angle = 270.0/50.0;
    //第一次在第135度时
    painter.rotate(135);
    for(int i=0;i<=50;i++){
        if(i%10 == 0){
            //长画刻度
            painter.drawLine(height()/2-20,0,height()/2-3,0);
        }else{
            //画短的刻度线
            painter.drawLine(height()/2-8,0,height()/2-3,0);
        }
        //旋转
        painter.rotate(angle);
    }
}
