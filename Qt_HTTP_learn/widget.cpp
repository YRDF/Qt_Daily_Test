#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    QNetworkRequest req(QUrl("http://tianqiapi.com/index"));
    reply = manager->get(req);

    connect(manager,&QNetworkAccessManager::finished,this,[](){
        qDebug()<<"请求完成";
    });

    connect(reply,&QNetworkReply::finished,this,&Widget::readmessage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readmessage()
{
    QByteArray data = reply->readAll();
    qDebug()<<QString::fromUtf8(data);
}
