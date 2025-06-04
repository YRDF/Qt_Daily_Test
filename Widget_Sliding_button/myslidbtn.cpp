#include "myslidbtn.h"


MySlidBtn::MySlidBtn(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(60, 80);
    animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);

    animation->setStartValue(height()/2);
    animation->setEndValue(width()-height()/2);

    //根据曲线设置滑动的过程
    animation->setEasingCurve(QEasingCurve::InQuad);

    animation->setDuration(600);

    connect(animation,&QPropertyAnimation::valueChanged,this,[=](const QVariant &value){
        posX = value.toInt();
        update();
    });
}

void MySlidBtn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    int radius = height()/2;

    painter.setBrush(isOff?offBgBrush:onBgBrush);
    painter.drawRoundedRect(this->rect(),radius*0.9,radius*0.9);

    //画圆
    QPoint center;
    center.setX(posX);
    center.setY(radius);
    painter.setBrush(isOff?offRbBrush:onRbBrush);
    painter.drawEllipse(center,radius,radius);

    //画字
    painter.setPen(Qt::white);
    painter.drawText(this->rect(),Qt::AlignCenter,isOff?offText:onText);
}

void MySlidBtn::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        isOff? animation->setDirection(QAbstractAnimation::Forward):animation->setDirection(QAbstractAnimation::Backward);
        animation->start();
        //qDebug()<<"left btn clicked";
        emit isClicked();
        isClickedWithParams(isOff);
        isOff = !isOff;
    }
    QWidget::mousePressEvent(event);
}

void MySlidBtn::resizeEvent(QResizeEvent *event)
{
    animation->setStartValue(height()/2);
    animation->setEndValue(width()-height()/2);
}
