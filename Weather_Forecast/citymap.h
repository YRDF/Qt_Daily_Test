#ifndef CITYMAP_H
#define CITYMAP_H

#include <QMap>
#include <QWidget>
#include <QMouseEvent>
#include<QDebug>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QFile>

class CityMap
{
public:
    CityMap();
    QMap<QString,QString> saveMap = {};
    QString findCity(QString cityname);
    void initMap();
};

#endif // CITYMAP_H
