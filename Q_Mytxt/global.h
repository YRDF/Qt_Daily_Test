#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<QDebug>
#include<functional>
#include"QStyle"
#include<QFileDialog>
#include<QFile>
#include<QString>
#include<QDateTime>
#include <QTimer>
#include <QWheelEvent>

extern std::function<void (QWidget*)> repolish;

#endif // GLOBAL_H
