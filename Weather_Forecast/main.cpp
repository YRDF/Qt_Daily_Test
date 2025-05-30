#include "widget.h"

#include <QApplication>
#include <QFile>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 加载样式表
    QFile styleFile(":/style/stylesheet.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        a.setStyleSheet(style);
        styleFile.close();
        qDebug()<<"qss load ok";
    }
    Widget w;
    w.show();
    return a.exec();
}
