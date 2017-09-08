//
// Created by 贺江 on 2017/8/3.
//

#include "data_context.h"

DataContext::DataContext()
{
    free          = false;
    duration = 0;
}

DataContext::~DataContext()
{

}

AvFrameContext::AvFrameContext()
{
    frame           = av_frame_alloc();
    pixelFormat     = AV_PIX_FMT_NONE;
    sampleFormat    = AV_SAMPLE_FMT_NONE;
    pts             = -1;
    sampleRate      = 0;
    channels        = 0;
    type            = AVMEDIA_TYPE_UNKNOWN;

}

AvFrameContext::~AvFrameContext()
{
    if(frame != nullptr)
    {
        av_frame_unref(frame);
        av_frame_free(&frame);

        frame = nullptr;
    }

}

AvFrameContext *AvFrameContext::clone()
{
    AvFrameContext *frameCtx = new AvFrameContext;

    av_frame_unref(frameCtx->frame);
    av_frame_free(&frameCtx->frame);

    frameCtx->pts              = this->pts;
    frameCtx->frame            = av_frame_clone(this->frame);
    frameCtx->pixelFormat      = this->pixelFormat;
    frameCtx->sampleFormat     = this->sampleFormat;
    frameCtx->sampleRate       = this->sampleRate;
    frameCtx->channels         = this->channels;
    frameCtx->duration         = this->duration;
    frameCtx->type             = this->type;

    return frameCtx;
}

void DataContext::addFrame(AvFrameContext *frame)
{
    QMutexLocker locker(&mutex);

   if(duration == 0)
       duration = frame->duration;

    if(!free && queue.length() < 100)
    {
        queue.push_back(frame);

        waitCondition.wakeAll();

    } else
    {
        delete frame;
    }

}

AvFrameContext *DataContext::getFrame()
{
    AvFrameContext *frame = nullptr;

    mutex.lock();

    if(queue.length() == 0 && !free)
        waitCondition.wait(&mutex);

    if(queue.length() > 0)
        frame = queue.takeFirst();

    if(frame != nullptr)
        curPts = frame->pts;

    mutex.unlock();

    return frame;
}

int64_t DataContext::getNextPts()
{
    QMutexLocker locker(&mutex);

    if(queue.length() != 0)
        return queue[0]->pts;

    return curPts + duration;
}

int DataContext::getBufferLength()
{
    if(queue.length() != 0)
        return queue[queue.length() - 1]->pts - queue[0]->pts;

    return 0;
}

void DataContext::terminal()
{
    QMutexLocker locker(&mutex);

    free = true;

    waitCondition.wakeAll();
}

void DataContext::disponse()
{
    QMutexLocker locker(&mutex);

    while (queue.length() > 0)
    {
        delete queue.takeFirst();
    }

}
