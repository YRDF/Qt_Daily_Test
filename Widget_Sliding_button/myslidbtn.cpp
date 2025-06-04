#include "myslidbtn.h"


MySlidBtn::MySlidBtn(QWidget *parent)
    : QWidget{parent}
{
    change = true;
}

void MySlidBtn::paintEvent(QPaintEvent *event)
{
    QPainter mypain(this);
    mypain.setRenderHint(QPainter::Antialiasing);
    mypain.setBrush(change?Qt::black:Qt::gray);
    mypain.setPen(Qt::NoPen);
    //宽高
    int Hig = height()/2;
    int Len = width();
    mypain.drawRoundedRect(this->rect(),Hig,Hig);

    //画圆
    mypain.setBrush(change?Qt::red:Qt::green);
    mypain.setPen(Qt::NoPen);
    // 添加尺寸有效性检查 - 关键修复点
    if (width() <= 0 || height() <= 0) {
        return; // 避免在无效尺寸下绘制
    }
    mypain.drawEllipse(QPoint((change?Hig:Len-Hig),Hig),Hig*0.9,Hig*0.9);

    //写字
    mypain.setPen(Qt::white);
    mypain.drawText(this->rect(),Qt::AlignCenter,change?"OFF":"ON");
}

void MySlidBtn::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug()<<"left btn clicked";
        change = !change;
        update();
    }
    QWidget::mousePressEvent(event);
}
