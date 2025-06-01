#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(369,597);
    setWindowFlag(Qt::FramelessWindowHint);

    menuQuit = new QMenu(this);
    menuQuit->setStyleSheet("QMenu::item {color:pink;border-radius:7px}");
    QAction *closeAct = new QAction(QIcon(":/res/close.png"),tr("退出"),this);
    menuQuit->addAction(closeAct);

    connect(menuQuit,&QMenu::triggered,this,[=](){
        this->close();
    });

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    //http://t.weather.itboy.net/api/weather/city/101010100
    QUrl urlWeather("http://t.weather.itboy.net");
    QNetworkRequest request(urlWeather);
    reply = manager->get(request);

    connect(manager,&QNetworkAccessManager::finished,this,[](){
        qDebug()<<"url request finish";
    });

    connect(reply,&QNetworkReply::finished,this,&Widget::readHttpReply);

    mbx = new QMessageBox(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readHttpReply()
{
    //判断是否返回错误
    int respCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //qDebug()<<"respCode is: "<<respCode;
    if(reply->error() == QNetworkReply::NoError && respCode==200){
        QByteArray data = reply->readAll();
        qDebug()<<QString::fromUtf8(data);
    }else{
        mbx->setWindowTitle("错误！");
        mbx->setText("网络请求失败！");
        mbx->setStyleSheet("QPushButton{color:white}");
        mbx->setStandardButtons(QMessageBox::Ok);
        mbx->exec();
        qDebug()<<"请求失败！"<<reply->errorString();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        //qDebug()<<"right mouse button clicked";
        menuQuit->exec(QCursor::pos());
    }
    if(event->button() == Qt::LeftButton){
        //qDebug()<<"left mouse button clicked";
        //鼠标当前位置
        // qDebug()<<event->globalPosition();
        //窗口当前位置
        // qDebug()<<this->pos();
        movepoint = this->pos()-event->globalPosition();
        //qDebug()<<movepoint;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move((event->globalPosition()+movepoint).toPoint());
}
