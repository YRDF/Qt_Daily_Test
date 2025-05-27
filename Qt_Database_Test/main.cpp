#include "widget.h"

#include <QApplication>
#include<QSqlDatabase>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    qDebug()<<"hello world!";
    QStringList ls = QSqlDatabase::drivers();
    qDebug()<< ls;
    return a.exec();
}
