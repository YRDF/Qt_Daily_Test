#ifndef DAYS_H
#define DAYS_H
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

class Days
{
public:
    Days();

    QString mData;
    QString mWeek;
    QString mCity;
    QString mTemp;
    QString mWeaType;
    QString mTempLow;
    QString mTempHig;

    QString mTips;
    QString mFx;
    QString mFl;
    QString mPm25;
    QString mHuml;
    QString mAirQ;
};

#endif // DAYS_H
