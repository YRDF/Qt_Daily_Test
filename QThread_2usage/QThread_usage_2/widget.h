#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "thread2.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
signals:
    void sentNum(int num);
    void StarSort(QVector<int>);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void randNumShow(QVector<int> TVec);
    void sortNumShow(QVector<int> sortVec);
private:
    Ui::Widget *ui;
    int use_Num = 5;
    QVector<int> ShowrandVec;
    QVector<int> ShowSortVec;
};
#endif // WIDGET_H
