#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    unsigned version = avcodec_version();
    unsigned major = (version >> 16) & 0xFF; // 主版本
    unsigned minor = (version >> 8) & 0xFF;  // 次版本
    unsigned patch = version & 0xFF;         // 补丁版本
    QString QVs = QString("%1.%2.%3").arg(major).arg(minor).arg(patch);
    qDebug()<<"version is: "<<QVs;

    this->setWindowTitle(tr("录音测试"));

    //1.注册输入设备
    avdevice_register_all();
    //2.获取输入的格式

    //3.打开输入设备
    //4.采集数据
    //5.关闭设备，关闭文件，回收格式上下的堆区空间
    QThread *t1 = new QThread();
    audiothread *ad = new audiothread();
    ad->moveToThread(t1);

    t1->start();
    connect(ui->pushButton,&QPushButton::clicked,ad,&audiothread::audioOperater);
    connect(t1, &QThread::finished, ad, &QObject::deleteLater);
    connect(t1, &QThread::finished, t1, &QObject::deleteLater);
    qDebug()<<"this main thread is : "<<QThread::currentThreadId();

    connect(ui->stopBtn,&QPushButton::clicked,this,[=](){
        ad->setStopBool(true);
        qDebug()<<"stoprecoding";

        t1->exit();
        t1->wait();
    });
}

Widget::~Widget()
{
    delete ui;
}
