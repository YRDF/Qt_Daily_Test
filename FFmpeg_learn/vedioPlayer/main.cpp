#include "widget.h"
#include <QApplication>



/*// 将RGB帧保存为PPM格式文件
void SaveFrame(AVFrame *pFrame, int width, int height, int index) {
    FILE *pFile;
    char szFilename[32];
    int y;

    // 创建文件名：frame0.ppm, frame1.ppm...
    sprintf(szFilename, "frame%d.ppm", index);
    //"wb" 模式表示以二进制写入模式打开文件。"w" 表示写入模式，"b" 表示二进制模式。
    pFile = fopen(szFilename, "wb");

    if (pFile == NULL)
        return;

    // 写入PPM文件头：P6表示二进制格式，宽高，最大颜色值255
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // 逐行写入RGB数据
    for (y = 0; y < height; y++) {
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);
    }

    fclose(pFile);
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
