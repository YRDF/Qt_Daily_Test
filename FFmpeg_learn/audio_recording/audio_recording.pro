QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audioplay.cpp \
    audiothread.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    audioplay.h \
    audiothread.h \
    widget.h

FORMS += \
    widget.ui

INCLUDEPATH += $$PWD/ffmpeg_qt_use/include


LIBS += $$PWD/ffmpeg_qt_use/lib/avcodec.lib\
        $$PWD/ffmpeg_qt_use/lib/avdevice.lib\
        $$PWD/ffmpeg_qt_use/lib/avfilter.lib\
        $$PWD/ffmpeg_qt_use/lib/avformat.lib\
        $$PWD/ffmpeg_qt_use/lib/avutil.lib\
        $$PWD/ffmpeg_qt_use/lib/postproc.lib\
        $$PWD/ffmpeg_qt_use/lib/swresample.lib\
        $$PWD/ffmpeg_qt_use/lib/swscale.lib

INCLUDEPATH += G:\cppsoft\SDL\SDL2-2.32.8\x86_64-w64-mingw32\include

LIBS += G:\cppsoft\SDL\SDL2-2.32.8\x86_64-w64-mingw32\bin\SDL2.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
