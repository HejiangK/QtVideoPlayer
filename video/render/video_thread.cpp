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
    int64_t         realTime        = 0;
    int64_t         lastPts         = 0;
    int64_t         delay           = 0;
    int64_t         lastDelay       = 0;

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


        if(audioRender != nullptr)
        {
            realTime = audioRender->getCurAudioTime();

            if(lastPts == 0)
                lastPts = videoFrame->pts;

            lastDelay   = delay;
            delay       = videoFrame->pts - lastPts;

            lastPts = videoFrame->pts;

            if(delay < 0 || delay > 1000000)
            {
                delay = lastDelay != 0 ? lastDelay : 0;
            }

            if(delay != 0)
            {
                if(videoFrame->pts > realTime)
                    QThread::usleep(delay * 1.5);
//                else
//                    QThread::usleep(delay / 1.5);
            }
        }

        QImage img(imageContext->buffer, size.width(), size.height(), QImage::Format_RGB32);

        emit onFrame(img);

        delete videoFrame;

    }

    delete imageContext;

    this->deleteLater();
}

void VideoThread::setAudio(AudioRender *audioRender)
{
    this->audioRender = audioRender;
}
