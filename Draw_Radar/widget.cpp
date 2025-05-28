#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer,QTimer::timeout,this,[=](){
        //qDebug()<<"test";
        SAngle += 30;
        update();
        if(SAngle >=360)
            SAngle=0;
    });
    timer->setInterval(100);
    timer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // QPainter painter(this);
    // //精细设置画笔
    // QPen pen(Qt::blue,3);
    // painter.setPen(pen);
    // //一个矩形
    // QRectF rectangle(0,0,200,200);
    // painter.drawRect(rectangle);
    // //移动坐标原点到rect的中心
    // painter.translate(rect().center());
    // painter.drawRect(0,0,200,200);

    //开始画雷达
    QPainter painter(this);
    //画刷
    painter.setBrush(QBrush(Qt::black));
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //画刷填充
    painter.drawRect(rect());
    //取消画刷，否则画的圆也会被填充为画刷的颜色，遮挡之前画的圆
    painter.setBrush(Qt::NoBrush);
    //画笔
    painter.setPen(QPen(Qt::green,3));
    //移动中心
    painter.translate(rect().center());
    // painter.drawEllipse(QPoint(0,0),100,100);
    // painter.drawEllipse(QPoint(0,0),200,200);
    //画7个圆
    //在这里要用double，因为坐标大小为700
    //如果整除会出现余数消失，导致有一些像素丢失
    double rEve = height()/2.0/7.0;
    double dataTemp = rEve*7.0;
    for(int i=1;i<=7;i++){
        painter.drawEllipse(QPoint(0,0),rEve*i,rEve*i);
    }
    //画坐标轴
    painter.drawLine(QPoint(-height()/2,0),QPoint(height()/2,0));
    painter.drawLine(QPoint(0,-height()/2),QPoint(0,height()/2));

    //扇形设置锥型渐变
    QConicalGradient conGradient(0,0,-SAngle);
    conGradient.setColorAt(0,QColor(0,255,0,200));
    conGradient.setColorAt(0.1,QColor(0,255,0,100));
    conGradient.setColorAt(0.2,QColor(0,255,0,0));
    conGradient.setColorAt(1,QColor(0,255,0,0));
    //画刷
    painter.setPen(Qt::NoPen);
    painter.setBrush(conGradient);
    //在矩形中画扇形
    QRectF rectangle(-dataTemp,-dataTemp,dataTemp*2,dataTemp*2);
    int startAngle = SAngle * 16;
    int spanAngle = 70 * 16;
    painter.drawPie(rectangle, -startAngle, spanAngle);

}
