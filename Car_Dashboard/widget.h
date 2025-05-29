#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include<QPainter>
#include<QTimer>
#include<QtMath>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event)override;

private:
    Ui::Widget *ui;
    QTimer *timer;
    int currentvalue;
    int mark = 0;
    //旋转一个刻度是多少度
    double angle = 240.0/60.0;
    //起始度数
    int starAngle;
    //初始化画布
    void initCanvas(QPainter& painter);
    //画小圆
    void drawMiddleCircle(QPainter& painter,int r);
    //画小圆中的当前速度
    void drawCurrentSpeed(QPainter& painter);
    //画刻度
    void drawScale(QPainter& painter,int radius);
    //写刻度文字
    void drawScaleText(QPainter& painter,int radius);
    //画指针
    void drawPointLine(QPainter& painter,int length);
    //画扇形
    void drawSpeedPie(QPainter& painter,int radius);
    //画内圈
    void drawEllipseInner(QPainter& painter,int radius);
    //画一个红色圆圈，之后被黑色遮挡就显示红色光圈了
    void drawEllipseInnerShine(QPainter& painter,int radius);
    //外环扇形
    void drawEllipseOutShine(QPainter& painter,int radius);
    //定时器
    void starSpeed();
    //画图片
    void drawLogo(QPainter& painter,int radius);
};
#endif // WIDGET_H
