#include "audioplay.h"

audioPlay::audioPlay(QObject *parent)
    : QObject{parent}
{}

int bufferLen;          // 全局变量：剩余待处理的音频数据长度
char* bbufferData;      // 全局变量：指向当前音频数据位置的指针

void _audioCallback(void *userdata, Uint8 * stream,
                                 int len){
    // 1. 清空目标音频缓冲区（设置为静音）
    SDL_memset(stream,0,len);
    if(bufferLen ==0){
        return;
    }
    // 3. 计算实际需要复制的数据量
    len = (len>bufferLen)?bufferLen:len;        // 避免复制超过可用数据量
    // 4. 将音频数据混合到输出流
    SDL_MixAudio(stream,(Uint8*)bbufferData,len,SDL_MIX_MAXVOLUME);

    // 5. 更新指针和剩余数据长度
    bbufferData += len;
    bufferLen -= len;
}

void audioPlay::sdl2Play()
{
    qDebug()<<"this audio play thread is : "<<QThread::currentThreadId();
    SDL_version version;
    SDL_VERSION(&version);
    qDebug()<<"sdl version is :"<<version.major<<version.minor<<version.patch;

    //使用SDL播放音频步骤
    //1.sdl分成各种子系统
    //初始化音频子系统
    SDL_Init(SDL_INIT_AUDIO);
    //2.确定播放音频的相关参数：
    SDL_AudioSpec spc;
    spc.freq = 44100;
    spc.format = AUDIO_S16LSB;
    spc.channels = 2;
    spc.callback = _audioCallback;
    spc.samples = 1024;

    //3.打开文件
    QFile file("./test.pcm");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"文件打开失败";
        SDL_Quit();
        return;
    }
    //打开音频设备
    SDL_OpenAudio(&spc,nullptr);
    //播放音频或者以后的视频，都是通过推流和拉流实现
    //PUSH：推流，程序主动推送数据给设备
    //PULL：拉流，音频设备主动向程序拉取数据
    SDL_PauseAudio(0); //0为播放，1为暂停
    char audo_buf[4096];
    while(1){
        bufferLen = file.read(audo_buf,sizeof(char[4096]));
        if(bufferLen <=0){
            break;  //到了文件末尾
        }
        bbufferData = audo_buf;
        //休眠等待下一次拉取
        while(bufferLen>0){
            SDL_Delay(1);
        }
    }

}
