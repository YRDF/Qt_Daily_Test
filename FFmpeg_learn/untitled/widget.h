#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QFileDialog>
#include<QDebug>
#include<QColorDialog>
#include<QErrorMessage>
#include<QTimer>
#include<QThread>
#include "timethread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void showNowTime(const QString &message);
private:
    Ui::Widget *ui;
    QTimer *timer;
};
#endif // WIDGET_H
