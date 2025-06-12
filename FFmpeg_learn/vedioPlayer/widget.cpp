#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    t1 = new QThread();
    screenShot = new screenshotThread();
    screenShot->moveToThread(t1);

    connect(t1,&QThread::started,screenShot,&screenshotThread::screenShot);
    t1->start();
    //回收资源
    connect(screenShot,&screenshotThread::screenShootFinish,this,&Widget::Recyclet1);
    //把图片传过来，绘制到widget上
    connect(screenShot,&screenshotThread::sig_GetOneFrame,this,&Widget::RecvOneFrame);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::Recyclet1()
{
    if (t1->isRunning()){
        t1->quit();
        t1->wait();
    }
    // 删除子线程相关对象
    delete t1;
    delete screenShot;
}

void Widget::RecvOneFrame(QImage oneFram)
{
    mImage = oneFram;
    update(); //调用update将执行 paintEvent函数
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

    if (mImage.size().width() <= 0) return;

    //scaled函数:将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);
    //当前窗口长宽减去缩放后的长宽
    int x = this->width() - img.width();
    int y = this->height() - img.height();
    //将图像水平和垂直居中。
    x /= 2;
    y /= 2;
    painter.drawImage(QPoint(x,y),img); //画出图像
}
