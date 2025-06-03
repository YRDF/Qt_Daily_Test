#ifndef WIDGET_H
#define WIDGET_H

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
#include"citymap.h"
#include"picmap.h"
#include"days.h"
#include<QList>
#include<QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    //存放7个Days的数组
    Days days[7];
    QList<QLabel *> mDaylist;
    QList<QLabel *> mDatelist;
    QList<QLabel *> mWIconlist;
    QList<QLabel *> mWeatherlist;
    QList<QLabel *> mQualitylist;
    QList<QLabel *> mFxlist;
    QList<QLabel *> mFllist;
    //初始化这些list
    void initAllList();

    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void readHttpReply(QNetworkReply *reply);
protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    Ui::Widget *ui;
    QMenu *menuQuit;
    QPointF movepoint;
    QNetworkReply *reply;
    QMessageBox *mbx;
    QNetworkAccessManager* manager;
    QString StringWeather;
    void parseWeatherJsonData(QByteArray& rawData);
    void parseWeatherJsonDataNew(QByteArray& rawData);
    void drawTempLine();
    void drawTempLinelow();
    //QString getCity(QString cityname);
    CityMap citymap;
    PicMap picmap;
    void UpdateUI();
};
#endif // WIDGET_H
