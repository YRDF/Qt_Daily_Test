#ifndef PICMAP_H
#define PICMAP_H
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

class PicMap
{
public:
    PicMap();
    QMap<QString,QString> mTypeMap;
};

#endif // PICMAP_H
