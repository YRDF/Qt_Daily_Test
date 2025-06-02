#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setFixedSize(349,579);
    setWindowFlag(Qt::FramelessWindowHint);

    menuQuit = new QMenu(this);
    menuQuit->setStyleSheet("QMenu::item {color:pink;border-radius:7px}");
    QAction *closeAct = new QAction(QIcon(":/res/close.png"),tr("退出"),this);
    menuQuit->addAction(closeAct);

    connect(menuQuit,&QMenu::triggered,this,[=](){
        this->close();
    });

    manager = new QNetworkAccessManager(this);
    //http://t.weather.itboy.net/api/weather/city/101010100
    //http://gfeljm.tianqiapi.com/api?unescape=1&version=v61&appid=83773479&appsecret=MXtXkAd5

    StringWeather = "http://gfeljm.tianqiapi.com/api?unescape=1&version=v61&appid=83773479&appsecret=MXtXkAd5";
    QUrl urlWeather(StringWeather);
    QNetworkRequest request(urlWeather);
    reply = manager->get(request);

    connect(manager,&QNetworkAccessManager::finished,this,&Widget::readHttpReply);

    //connect(reply,&QNetworkReply::finished,this,&Widget::readHttpReply);

    mbx = new QMessageBox(this);
    ui->label_search->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readHttpReply(QNetworkReply *reply)
{
    //判断是否返回错误
    int respCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //qDebug()<<"respCode is: "<<respCode;
    if(reply->error() == QNetworkReply::NoError && respCode==200){
        QByteArray data = reply->readAll();
        parseWeatherJsonData(data);
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

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    // 检查事件是否来自目标Label
    if (obj == ui->label_search)
    {
        // 检测鼠标按下事件
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                //qDebug() << "Label被点击了!";
                // 在这里添加你的点击处理代码
                //ui->label_search->setText("已点击!");
                QString cityNameUser = ui->lineEdit->text();
                QString city_code = citymap.findCity(cityNameUser);
                if(city_code !=""){
                    StringWeather += "&cityid=" + city_code;
                    qDebug()<<StringWeather;
                    manager->get(QNetworkRequest(QUrl(StringWeather)));
                }else{
                    mbx->setWindowTitle("错误！");
                    mbx->setText("没有这个城市！");
                    mbx->setStyleSheet("QPushButton{color:white}");
                    mbx->setStandardButtons(QMessageBox::Ok);
                    mbx->exec();
                    qDebug()<<"城市请求失败！";
                    //<<reply->errorString()
                }
                return true;  // 表示事件已处理
            }
        }
    }

    // 其他事件交给基类处理
    return QWidget::eventFilter(obj, event);
}

void Widget::parseWeatherJsonData(QByteArray &rawData)
{
    //bytearray数据转换为json文件
    QJsonDocument jsparseDoc = QJsonDocument::fromJson(rawData);
    if(!jsparseDoc.isNull() &&jsparseDoc.isObject()){
        //json文件转换为jsonobject
        QJsonObject jsparseObj = jsparseDoc.object();
        //解析日期
        QString date  = jsparseObj["date"].toString();
        QString week  = jsparseObj["week"].toString();
        ui->label_current_date->setText(date+"  "+week);
        //解析城市，当前温度，天气风向等其他信息
        QString cityName = jsparseObj["city"].toString();
        ui->label_city->setText(cityName+"市");
        QString currentTemp = jsparseObj["tem"].toString();
        ui->label_tmp_now->setText(currentTemp+"℃");
        ui->label_tmp->setText(jsparseObj["tem2"].toString()+"℃ ~ "
                               +jsparseObj["tem1"].toString()+"℃");
        ui->label_weather->setText(jsparseObj["wea"].toString());
        ui->label_close_suggest->setText(jsparseObj["air_tips"].toString());
        ui->label_wind_info->setText(jsparseObj["win"].toString());
        ui->label_windy_level->setText(jsparseObj["win_speed"].toString());
        ui->label_pm25_info->setText(jsparseObj["air_pm25"].toString());
        ui->label_humidity_info->setText(jsparseObj["humidity"].toString());
        ui->label_air_quality_info->setText(jsparseObj["air_level"].toString());
        ui->label->setPixmap(picmap.mTypeMap[jsparseObj["wea"].toString()]);
    }

}

// QString Widget::getCity(QString cityname)
// {
//     QFile file(":/citycode.json");
//     file.open(QIODevice::ReadOnly);
//     QByteArray rawData = file.readAll();
//     file.close();
//     QJsonDocument jsDoc = QJsonDocument::fromJson(rawData);
//     if(jsDoc.isArray()){
//         QJsonArray citys = jsDoc.array();
//         for(QJsonValue val:citys){
//             if(val.isObject()){
//                 QString city_name = val["city_name"].toString();
//                 if(city_name == cityname){
//                     return val["city_code"].toString();
//                 }
//             }
//         }
//         return "";
//     }
// }
