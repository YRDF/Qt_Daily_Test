#ifndef AUDIOPLAY_H
#define AUDIOPLAY_H

#include <QObject>
#include<QDebug>
#include<QThread>
#include<SDL2/SDL.h>
#include<QFile>

class audioPlay : public QObject
{
    Q_OBJECT
public:
    explicit audioPlay(QObject *parent = nullptr);
    void sdl2Play();
signals:
};

#endif // AUDIOPLAY_H
