#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    currentvalue = 0;
    connect(timer,&QTimer::timeout,this,[=](){
        if(mark == 0){
        currentvalue++;
        if(currentvalue>=51){
            mark = 1;
            }
        }if(mark == 1){
            currentvalue--;
            if(currentvalue == 0){
                mark = 0;
            }
        }
        update();
    });
    timer->start(50);
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

    //当前值
    painter.setFont(QFont("华文宋体",25));
    //painter.drawText(0,0,QString::number(currentvalue));
    painter.drawText(QRect(-60,-60,120,120),Qt::AlignCenter,QString::number(currentvalue));

    //旋转坐标轴
    //旋转一个刻度是多少度
    double angle = 270.0/50.0;
    painter.setFont(QFont("华文宋体",15));
    painter.save();//保存当前坐标位置
    //坐标偏移135度
    painter.rotate(135);
    for(int i=0;i<=50;i++){

        //画字
        if(i%10 == 0){
        if(135+angle *i< 270){
            //坐标旋转180度
            painter.rotate(180);
            painter.drawText(-(height()/2-20-10),8,QString::number(i));
            painter.rotate(-180);
        }else{
            painter.drawText(height()/2-20-30,8,QString::number(i));
        }
            }
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
    //画指针
    painter.restore();
    painter.save();
    painter.rotate(135 + angle * currentvalue);
    painter.drawLine(60,0,height()/2 - 20- 10 - 28,0);

    //画扇形
    painter.restore();
    QRect rentangle(-height()/2+58,-height()/2+58,height()-116,height()-116);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(235,152,50,150));
    painter.drawPie(rentangle,(360-135)*16,-angle*currentvalue*16);
}
