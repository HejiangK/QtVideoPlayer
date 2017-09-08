//
// Created by 贺江 on 2017/8/4.
//

#ifndef APP_AVU_IMAGE_CVT_H
#define APP_AVU_IMAGE_CVT_H

extern "C"
{
#include <libavutil/time.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/imgutils.h>
};

class ImageConvert
{
public:
    ImageConvert(AVPixelFormat in_pixelFormat, int in_width, int in_height,
                    AVPixelFormat out_pixelFormat, int out_width, int out_height);

    virtual ~ImageConvert();

    void convertImage(AVFrame *frame);

public:

    SwsContext      *swsContext;

    AVFrame         *frame;

    uint8_t         *buffer;

    AVPixelFormat   in_pixelFormat;

    AVPixelFormat   out_pixelFormat;

    int             in_width;

    int             in_height;

    int             out_width;

    int             out_height;

};


#endif //APP_AVU_IMAGE_CVT_H
