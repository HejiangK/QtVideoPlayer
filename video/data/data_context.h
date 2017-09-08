//
// Created by 贺江 on 2017/8/3.
//

#ifndef APP_CTX_DATA_H
#define APP_CTX_DATA_H

#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <QDebug>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/time.h>
};


const AVRational time_base_q = {1,AV_TIME_BASE};

class AvFrameContext
{
public:

    AVFrame         *frame;

    int64_t         pts;

    AVPixelFormat   pixelFormat;

    AVSampleFormat  sampleFormat;

    int             sampleRate;

    int             channels;

    int             duration;

    AVMediaType     type;

    AvFrameContext();

    virtual ~AvFrameContext();

    AvFrameContext *clone();
};

class DataContext
{
public:

    DataContext();

    virtual ~DataContext();

    virtual void addFrame(AvFrameContext *frame);

    virtual AvFrameContext *getFrame();

    virtual int64_t getNextPts();

    virtual void terminal();

    virtual void disponse();

    virtual int getBufferLength();

protected:

    QMutex                  mutex;

    QWaitCondition          waitCondition;

    QList<AvFrameContext*>     queue;

    bool                    free;

    int64_t                 duration;

    int64_t                 curPts;

};


#endif //APP_CTX_DATA_H
