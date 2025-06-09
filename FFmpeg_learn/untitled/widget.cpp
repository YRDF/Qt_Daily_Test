#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);  // 设置 LCD 样式
    ui->lcdNumber->setStyleSheet("QLCDNumber { background: black; color: green; }");  // 背景黑色，数字绿色

    connect(timer,&QTimer::timeout,this,[this](){
        QTime currentTime = QTime::currentTime();  // 获取当前时间
        ui->lcdNumber->display(currentTime.toString("HH:mm:ss"));
    });
    timer->start(500);


    QThread *t1 = new QThread();
    timeThread *tim = new timeThread();
    tim->moveToThread(t1);


    connect(t1, &QThread::started, tim, &timeThread::startTimers);
    connect(tim,&timeThread::Nowtime,this,&Widget::showNowTime);
    t1->start();
    qDebug()<<QThread::currentThreadId();
    // 线程退出时自动清理
    connect(t1, &QThread::finished, tim, &QObject::deleteLater);
    connect(t1, &QThread::finished, t1, &QObject::deleteLater);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    // QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框"),"D:",tr("图片文件(*png *jpg)"));
    // qDebug()<<fileName;
    // QColor cilor = QColorDialog::getColor(Qt::red,this,tr("颜色对话框"),QColorDialog::ShowAlphaChannel);
    // qDebug()<<cilor;
    // QErrorMessage *msg = new QErrorMessage(this);
    // msg->setWindowTitle(tr("错误信息"));
    // msg->showMessage(tr("大错特错"));
    ui->label->setText(tr("hello world!"));
}

void Widget::showNowTime(const QString &message)
{
    qDebug()<<message;
    ui->label_2->setText(message);
}

