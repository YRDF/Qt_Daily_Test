#ifndef MYSLIDBTN_H
#define MYSLIDBTN_H

#include <QWidget>
#include<QPainter>
#include<QDebug>
#include <QMouseEvent>

class MySlidBtn : public QWidget
{
    Q_OBJECT
public:
    explicit MySlidBtn(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    bool change;
signals:
};

#endif // MYSLIDBTN_H
