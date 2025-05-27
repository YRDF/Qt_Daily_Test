#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"global.h"

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
    QFile file;
    bool eventFilter(QObject *watched, QEvent *event)override;
private:
    Ui::Widget *ui;
    QTimer *timer;
private slots:
    void updateTime();
};
#endif // WIDGET_H
