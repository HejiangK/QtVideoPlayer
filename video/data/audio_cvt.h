//
// Created by 贺江 on 2017/8/4.
//

#ifndef APP_AVU_AUDIO_CVT_H
#define APP_AVU_AUDIO_CVT_H

extern "C"
{
#include <libavutil/time.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/imgutils.h>
};

class AudioConvert
{

public:
    AudioConvert(AVSampleFormat in_sample_fmt, int in_sample_rate, int in_channels,
                    AVSampleFormat out_sample_fmt, int out_sample_rate, int out_channels);

    virtual ~AudioConvert();

    /**
     * 初始化buffer
     * @param audioContext 需要被初始化的context
     * @param nb_samples 音频数据长度
     * **/
    int allocContextSamples(int nb_samples);

    /**
     * 转换音频数据格式
     * @param frame 需要被转换的音频frame
     * @param audioContext 转换器
     * **/
    int convertAudio(AVFrame *frame);


public:

    SwrContext      *swrContext;

    uint8_t         **buffer;

    AVSampleFormat  in_sample_fmt;

    AVSampleFormat  out_sample_fmt;

    int             in_sample_rate;

    int             out_sample_rate;

    int             in_channels;

    int             out_channels;

    int             bufferLen;

    bool            invalidated;

};


#endif //APP_AVU_AUDIO_CVT_H
