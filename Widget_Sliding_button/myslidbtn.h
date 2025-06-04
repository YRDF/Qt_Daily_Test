#ifndef MYSLIDBTN_H
#define MYSLIDBTN_H

#include <QWidget>
#include<QPainter>
#include<QDebug>
#include <QMouseEvent>
#include<QPropertyAnimation>


class MySlidBtn : public QWidget
{
    Q_OBJECT
public:
    explicit MySlidBtn(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

signals:
    void isClicked();
    void isClickedWithParams(bool);
private:
    bool isOff = true;
    QBrush offBgBrush = Qt::black;
    QBrush offRbBrush = Qt::red;

    QBrush onBgBrush = Qt::gray;
    QBrush onRbBrush = Qt::green;

    QString offText = "OFF";
    QString onText = "ON";

    QPropertyAnimation *animation;
    int posX = height()/2;
};

#endif // MYSLIDBTN_H
