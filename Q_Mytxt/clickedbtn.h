#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H

#include<QPushButton>
#include"global.h"

class ClickedBtn:public QPushButton
{
    Q_OBJECT
public:
    ClickedBtn(QWidget* parent = nullptr);
    ~ClickedBtn();
    void SetState(QString normal, QString hover, QString press);
protected:
    virtual void enterEvent(QEnterEvent *event); // 鼠标进入
    virtual void leaveEvent(QEvent *event);// 鼠标离开
    virtual void mousePressEvent(QMouseEvent *event) override; // 鼠标按下
    virtual void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放
private:
    QString _normal;
    QString _hover;
    QString _press;
};

#endif // CLICKEDBTN_H
