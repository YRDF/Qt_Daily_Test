#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    starAngle=150;
    starSpeed();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    initCanvas(painter);
    //QRadialGradient radialGradient(0, 0, height()/2);
    // // 设置颜色停靠点
    // radialGradient.setColorAt(0.0, QColor(255,0,0,50)); // 中心颜色
    // radialGradient.setColorAt(1.0, QColor(255,0,0,250));  // 外围颜色
    // // 使用这个渐变创建 QBrush
    // QBrush brush(radialGradient);
    // painter.setBrush(brush);

    drawMiddleCircle(painter,60);

    drawCurrentSpeed(painter);

    drawScale(painter,height()/2);

    painter.save();//保存当前坐标位置

    drawScaleText(painter,height()/2);

    drawPointLine(painter,height()/2-58);

    drawSpeedPie(painter,height());
}

void Widget::initCanvas(QPainter& painter)
{
    painter.setBrush(QBrush(Qt::black));
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(rect());
    //平移坐标
    painter.translate(rect().center());
}

void Widget::drawMiddleCircle(QPainter &painter,int r)
{
    // 画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),r,r);
}

void Widget::drawCurrentSpeed(QPainter &painter)
{
    //当前值
    painter.setFont(QFont("华文宋体",25));
    //painter.drawText(0,0,QString::number(currentvalue));
    painter.drawText(QRect(-60,-60,120,120),Qt::AlignCenter,QString::number(currentvalue));
}

void Widget::drawScale(QPainter &painter,int radius)
{
    painter.setFont(QFont("华文宋体",15));
    painter.save();//保存当前坐标位置
    //坐标偏移150度
    painter.rotate(starAngle);
    for(int i=0;i<=60;i++){
        if(i%5 == 0){
            //长画刻度
            painter.drawLine(radius-20,0,radius-3,0);
        }else{
            //画短的刻度线
            painter.drawLine(radius-8,0,radius-3,0);
        }
        //旋转
        painter.rotate(angle);
    }
    painter.restore();
}

void Widget::drawScaleText(QPainter &painter, int radius)
{
    //写刻度文字
    //半径
    int r = radius-40;
    for(int i=0;i<=60;i++){
        if(i%5 == 0){
            //保存坐标系
            painter.save();
            //算出平移点
            int deltX = qCos(qDegreesToRadians(210-angle*i))*r;
            int deltY = qSin(qDegreesToRadians(210-angle*i))*r;
            //平移坐标系
            painter.translate(deltX,-deltY);
            //旋转坐标系
            painter.rotate(-120+angle*i);//angle=4,i*4=120时，实际参数是0，不旋转
            //写上文字
            painter.drawText(-20,-20,40,40,Qt::AlignCenter,QString::number(i*4));
            //恢复坐标系
            painter.restore();
        }
    }
}

void Widget::drawPointLine(QPainter &painter,int length)
{
    //画指针
    painter.restore();
    painter.save();
    painter.rotate(starAngle + angle * currentvalue);
    painter.drawLine(60,0,length,0);

}

void Widget::drawSpeedPie(QPainter &painter, int radius)
{
    //画扇形
    painter.restore();
    QRect rentangle(-radius/2,-radius/2,radius,radius);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(235,152,50,starAngle));
    painter.drawPie(rentangle,(360-starAngle)*16,-angle*currentvalue*16);
}

void Widget::starSpeed()
{
    timer = new QTimer(this);
    currentvalue = 0;
    connect(timer,&QTimer::timeout,this,[=](){
        if(mark == 0){
            currentvalue++;
            if(currentvalue>=60){
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

