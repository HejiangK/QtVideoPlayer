//
// Created by 贺江 on 2017/9/8.
//

#include "video_thread.h"

VideoThread::VideoThread(QObject *parent) : QThread(parent)
{
    dataContext = new DataContext();
}

VideoThread::~VideoThread()
{

}

void VideoThread::setSize(const QSize &size)
{
    this->size = size;
}

DataContext *VideoThread::getDataContext()
{
    return dataContext;
}

void VideoThread::run()
{
    AvFrameContext  *videoFrame     = nullptr;
    ImageConvert    *imageContext   = nullptr;

    while (!isInterruptionRequested())
    {
        videoFrame = dataContext->getFrame();

        if(videoFrame == nullptr)
            break;

        if(imageContext != nullptr && (imageContext->in_width != videoFrame->frame->width ||
                                       imageContext->in_height != videoFrame->frame->height||
                                       imageContext->out_width != size.width() ||
                                       imageContext->out_height != size.height()))
        {
            delete imageContext;
            imageContext = nullptr;
        }

        if(imageContext == nullptr)
            imageContext = new ImageConvert(videoFrame->pixelFormat,
                                               videoFrame->frame->width,
                                               videoFrame->frame->height,
                                               AV_PIX_FMT_RGB32,
                                               size.width(),
                                               size.height());

        imageContext->convertImage(videoFrame->frame);


        QImage img(imageContext->buffer, size.width(), size.height(), QImage::Format_RGB32);

        emit renderFrame(img);

        delete videoFrame;

    }

    delete imageContext;
}
