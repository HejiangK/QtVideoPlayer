//
// Created by 贺江 on 2017/8/31.
//

#ifndef APP_AVI_FORMAT_H
#define APP_AVI_FORMAT_H

#include <QMutex>

#include "video/data/data_context.h"

class InputFormat
{
public:
    InputFormat();

    virtual ~InputFormat();

    int openFormat(const char *path);

    int openCodec(AVMediaType type);

    void setOption(const char *key,const char *value);

    void setInputFormat(const char *format);

    AvFrameContext *readFrame();

    void terminal();

    void setSynTime();

    int64_t getSynTime();

protected:

    double synchronize(AVFrame *srcFrame, double pts);

    static int onStreamTimeOut(void *param);

public:

    AVFormatContext     *formatContext;

    AVInputFormat       *inputFormat;

    AVCodecContext      *videoCodecContext;

    AVCodecContext      *audioCodecContext;

    AVCodec             *videoCodec;

    AVCodec             *audioCodec;

    AVStream            *videoStream;

    AVStream            *audioStream;

    AVPacket            *packet;

    AVDictionary        *options;

    int                 audioIndex;

    int                 videoIndex;

    double              video_clock;

    int64_t             synTime;

    QMutex              mutex;

};



#endif //APP_AVI_FORMAT_H
