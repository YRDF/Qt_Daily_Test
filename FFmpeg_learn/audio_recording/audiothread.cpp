#include "audiothread.h"

audiothread::audiothread(QObject *parent)
    : QObject{parent}
{}

void audiothread::setStopBool(bool b)
{
    this->stopAuSon = b;
}

void audiothread::audioOperater()
{
    qDebug()<<"this audio thread is : "<<QThread::currentThreadId();
    //2.获取windows采集数据所支持的格式：dshow
    const AVInputFormat* fmt = av_find_input_format("dshow");

    //定义录制音频格式上下文
    AVFormatContext* ctx = nullptr;
    //打开输入的音频设备
    const char* audio_device_name = "audio=麦克风 (Realtek(R) Audio)";
    avformat_open_input(&ctx,audio_device_name,fmt,nullptr);
    //采集的数据放入的文件 pcm是没任何编码格式的音频文件
    QFile au_file("./test.pcm");
    if(!au_file.open(QIODevice::WriteOnly)){
        qDebug()<<"打开失败！";
        return;
    }
    //采集音频数据 pkt采集包，ctx上下文,每次采集1帧，要循环采集
    AVPacket pkt;
    //int count = 20;
    stopAuSon = false;
    while(!stopAuSon && av_read_frame(ctx,&pkt) == 0){
        au_file.write((const char*)pkt.data,pkt.size);
        qDebug()<<"录制中.......";
    }
    //释放资源
    au_file.close();
    avformat_close_input(&ctx);
    qDebug()<<"stop 了";
}

