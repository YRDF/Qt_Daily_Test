#include "widget.h"
#include "ui_widget.h"


void Widget::initAllList()
{
    mDaylist<<ui->label_day_0<<ui->label_day_1<<ui->label_day_2<<ui->label_day_3
             <<ui->label_day_4<<ui->label_day_5;
    mDatelist<<ui->label_date_0<<ui->label_date_1<<ui->label_date_2<<ui->label_date_3
              <<ui->label_date_4<<ui->label_date_5;
    mWIconlist<<ui->label_weather_icon_0<<ui->label_weather_icon_1<<ui->label_weather_icon_2
               <<ui->label_weather_icon_3<<ui->label_weather_icon_4<<ui->label_weather_icon_5;
    mWeatherlist<<ui->label_weather_0<<ui->label_weather_1<<ui->label_weather_2<<ui->label_weather_3
                 <<ui->label_weather_4<<ui->label_weather_5;
    mQualitylist<<ui->label_quality_0<<ui->label_quality_1<<ui->label_quality_2<<ui->label_quality_3
                 <<ui->label_quality_4<<ui->label_quality_5;
    mFxlist<<ui->label_fx_0<<ui->label_fx_1<<ui->label_fx_2<<ui->label_fx_3
            <<ui->label_fx_4<<ui->label_fx_5;
    mFllist<<ui->label_fl_0<<ui->label_fl_1<<ui->label_fl_2<<ui->label_fl_3
            <<ui->label_fl_4<<ui->label_fl_5;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setFixedSize(349,579);
    setWindowFlag(Qt::FramelessWindowHint);
    initAllList();

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
    StringWeather = "http://gfeljm.tianqiapi.com/api?unescape=1&version=v9&appid=83773479&appsecret=MXtXkAd5";
    //StringWeather = "http://gfeljm.tianqiapi.com/api?unescape=1&version=v61&appid=83773479&appsecret=MXtXkAd5";
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
        parseWeatherJsonDataNew(data);
        //qDebug()<<QString::fromUtf8(data);

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

void Widget::parseWeatherJsonDataNew(QByteArray &rawData)
{
    //bytearray数据转换为json文件
    QJsonDocument jsparseDoc = QJsonDocument::fromJson(rawData);
    if(!jsparseDoc.isNull() &&jsparseDoc.isObject()){
        //json文件转换为jsonobject
        QJsonObject jsparseObj = jsparseDoc.object();
        days[0].mCity = jsparseObj["city"].toString();
        days[0].mPm25 = jsparseObj["aqi"].toObject()["pm25"].toString();
        if(jsparseObj.contains("data")&&jsparseObj["data"].isArray()){
            QJsonArray jsarry = jsparseObj["data"].toArray();
            for(int i =0;i<jsarry.size();i++){
                QJsonObject obj = jsarry[i].toObject();
                //qDebug()<<obj["date"].toString()<<obj["wea"].toString();
                days[i].mData = obj["date"].toString();
                days[i].mWeek = obj["week"].toString();
                days[i].mWeaType = obj["wea"].toString();
                days[i].mTemp = obj["tem"].toString();
                days[i].mTempLow = obj["tem2"].toString();
                days[i].mTempHig = obj["tem1"].toString();
                days[i].mFx = obj["win"].toArray()[0].toString();
                days[i].mFl = obj["win_speed"].toString();
                days[i].mAirQ = obj["air_level"].toString();
                days[i].mTips = obj["air_tips"].toString();
                days[i].mHuml = obj["humidity"].toString();
            }
        }
    }
    UpdateUI();
}

void Widget::UpdateUI()
{
    //解析日期
    ui->label_current_date->setText(days[0].mData+"  "+days[0].mWeek);
    //解析城市，当前温度，天气风向等其他信息
    //QString cityName = jsparseObj["city"].toString();
    //ui->label_city->setText(cityName+"市");
    QString currentTemp = days[0].mTemp;
    ui->label_city->setText(days[0].mCity+"市");
    ui->label_tmp_now->setText(currentTemp+"℃");
    ui->label_tmp->setText(days[0].mTempLow+"℃ ~ "
                           +days[0].mTempHig+"℃");
    ui->label_weather->setText(days[0].mWeaType);
    ui->label_close_suggest->setText(days[0].mTips);
    ui->label_wind_info->setText(days[0].mFx);
    ui->label_windy_level->setText(days[0].mFl);
    ui->label_pm25_info->setText(days[0].mPm25);
    ui->label_humidity_info->setText(days[0].mHuml);
    ui->label_air_quality_info->setText(days[0].mAirQ);
    ui->label->setPixmap(picmap.mTypeMap[days[0].mWeaType]);

    //修改下方widget的内容
    for(int i =0;i<6;i++){
        mDaylist[i]->setText(days[i].mWeek);
        QStringList dayList = days[i].mData.split("-");
        mDatelist[i]->setText(dayList.at(1)+"-"+dayList.at(2));
        //如果有转这个字就分割，把转之前的分了
        if(days[i].mWeaType.contains("转")){
            QStringList WeatherIconList = days[i].mWeaType.split("转");
            mWIconlist[i]->setPixmap(picmap.mTypeMap[WeatherIconList.at(0)]);}
        else{
            mWIconlist[i]->setPixmap(picmap.mTypeMap[days[i].mWeaType]);
        }

        QString airQ = days[i].mAirQ;
        if(airQ == "优"){
            mQualitylist[i]->setStyleSheet("background-color:rgb(0, 170, 51);color:rgb(235, 255, 255);border-radius:7px");
            mQualitylist[i]->setText(days[i].mAirQ);
        }else if(airQ == "良"){
            mQualitylist[i]->setStyleSheet("background-color:rgb(107,107,107);color:rgb(235, 255, 255);border-radius:7px");
            mQualitylist[i]->setText(days[i].mAirQ);
        }else{
            mQualitylist[i]->setStyleSheet("background-color:rgb(107,107,107);color:rgb(235, 255, 255);border-radius:7px");
            mQualitylist[i]->setText(days[i].mAirQ);
        }

        mWeatherlist[i]->setText(days[i].mWeaType);

        mFxlist[i]->setMinimumWidth(width()/6-10);
        mFxlist[i]->setMaximumWidth(width()/6-10);
        mFxlist[i]->setText(days[i].mFx);

        //如果有转这个字就分割，把转之前的分了
        mFllist[i]->setMinimumWidth(width()/6-10);
        mFllist[i]->setMaximumWidth(width()/6-10);
        if(days[i].mFl.contains("转")){
            QStringList FlList = days[i].mFl.split("转");
            mFllist[i]->setText(FlList.at(0));
        }else{
            mFllist[i]->setText(days[i].mFl);
        }
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
