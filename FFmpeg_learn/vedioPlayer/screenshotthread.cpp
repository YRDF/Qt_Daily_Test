#include "screenshotthread.h"

screenshotThread::screenshotThread(QObject *parent)
    : QObject{parent}
{}

int screenshotThread::screenShot()
{
    // 1. 初始化格式上下文
    if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0) {
        fprintf(stderr, "无法打开文件\n");
        return -1;
    }

    // 2. 获取流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        fprintf(stderr, "无法获取流信息\n");
        return -1;
    }

    // 3. 查找视频流
    for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }

    if (videoStream == -1) {
        fprintf(stderr, "未找到视频流\n");
        return -1;
    }

    // 4. 根据流信息获取解码器并创建编解码上下文
    pCodec = avcodec_find_decoder(pFormatCtx->streams[videoStream]->codecpar->codec_id);
    if (!pCodec) {
        fprintf(stderr, "解码器未找到\n");
        return -1;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx) {
        fprintf(stderr, "无法分配编解码上下文\n");
        return -1;
    }

    // 5. 复制编解码参数到上下文
    if (avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar) < 0) {
        fprintf(stderr, "无法复制编解码参数\n");
        return -1;
    }

    // 6. 打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        fprintf(stderr, "无法打开解码器\n");
        return -1;
    }

    // 7. 分配帧内存，目前是空的，需要用户输入
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    if (!pFrame || !pFrameRGB) {
        fprintf(stderr, "无法分配帧\n");
        return -1;
    }

    // 8. 设置RGB帧缓冲区
    //计算存储指定像素格式图像所需的内存大小
    //AV_PIX_FMT_RGB24：指定像素格式为 RGB24（每个像素占用 3 个字节，分别表示红、绿、蓝通道）
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
    //分配内存。
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    //将分配的内存绑定到 AVFrame 的数据数组中，并设置每行的字节数（linesize）。
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer,
                         AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);

    // 9. 初始化图像转换上下文，用于转换解码后的图像格式
    sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                             pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                             SWS_BILINEAR, NULL, NULL, NULL);

    pPacket = av_packet_alloc();
    if (!pPacket) {
        fprintf(stderr, "无法分配AVPacket\n");
        return -1;
    }

    // 10. 主循环：读取帧并处理
    /*
    从一个音视频文件中读取数据包，解码视频流中的帧，并将解码后的帧从原始格式（通常是 YUV）转换为 RGB 格式，
    最后调用 SaveFrameWithQt 函数保存或处理这些帧。整个过程会持续进行，直到读取到指定数量的帧（这里是 50 帧）为止。
    */
    while (av_read_frame(pFormatCtx, pPacket) >= 0) {
        //只处理视频流，所以判断是否为视频流
        if (pPacket->stream_index == videoStream) {
            // 发送数据包到解码器
            ret = avcodec_send_packet(pCodecCtx, pPacket);
            if (ret < 0) {
                fprintf(stderr, "解码错误 (send)\n");
                continue;
            }

            while (ret >= 0) {
                //从解码器接收解码后的帧
                ret = avcodec_receive_frame(pCodecCtx, pFrame);
                //如果返回 AVERROR(EAGAIN)，表示解码器需要更多输入数据（即需要调用 avcodec_send_packet）。
                //如果返回 AVERROR_EOF，表示解码结束。
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    break;
                else if (ret < 0) {
                    fprintf(stderr, "解码错误 (receive)\n");
                    break;
                }

                // 转换帧格式为RGB
                sws_scale(sws_ctx, (const uint8_t *const *)pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height,
                          pFrameRGB->data, pFrameRGB->linesize);

                // 保存帧
                //SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, frame_count++);
                SaveFrameWithQt(pFrameRGB, pCodecCtx->width, pCodecCtx->height, frame_count++);
                // 仅保存50帧
                if (frame_count >= 50) break;
            }
        }
        //释放 AVPacket 的内容。
        if (frame_count >= 50) break;
        av_packet_unref(pPacket);
    }
    emit screenShootFinish();
    return 0;
}

void screenshotThread::SaveFrameWithQt(AVFrame *frame, int width, int height, int index){
    // 1. 创建 QImage 对象
    QImage image(width, height, QImage::Format_RGB888);

    // 2. 将 FFmpeg 的 RGB 数据复制到 QImage
    for (int y = 0; y < height; y++) {
        // 获取当前行的指针
        uint8_t *src = frame->data[0] + y * frame->linesize[0];
        uint8_t *dst = image.scanLine(y);

        // 复制一行 RGB 数据
        memcpy(dst, src, width * 3);
    }

    // 3. 保存为 PNG 文件
    QString filename = QString("frame%1.png").arg(index, 4, 10, QLatin1Char('0'));
    image.save(filename, "PNG");

    //发送到主线程进行显示
    emit sig_GetOneFrame(image);

}

screenshotThread::~screenshotThread()
{
    // 11. 释放资源
    av_packet_free(&pPacket);
    av_frame_free(&pFrame);
    av_frame_free(&pFrameRGB);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);
    sws_freeContext(sws_ctx);
    av_freep(&buffer);
}
