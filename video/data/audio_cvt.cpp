//
// Created by 贺江 on 2017/8/4.
//

#include "audio_cvt.h"

AudioConvert::AudioConvert(AVSampleFormat in_sample_fmt, int in_sample_rate, int in_channels,
                                 AVSampleFormat out_sample_fmt, int out_sample_rate, int out_channels)
{

    this->in_sample_fmt		= in_sample_fmt;
    this->out_sample_fmt	= out_sample_fmt;
    this->in_channels		= in_channels;
    this->out_channels		= out_channels;
    this->in_sample_rate	= in_sample_rate;
    this->out_sample_rate	= out_sample_rate;
    this->swrContext		= swr_alloc_set_opts(nullptr,
                                                 av_get_default_channel_layout(out_channels),
                                                 out_sample_fmt,
                                                 out_sample_rate,
                                                 av_get_default_channel_layout(in_channels),
                                                 in_sample_fmt,
                                                 in_sample_rate, 0, nullptr);

    this->invalidated       = false;

    swr_init(this->swrContext);

    this->buffer = nullptr;

    this->buffer = (uint8_t**)calloc(out_channels,sizeof(**this->buffer));

}

AudioConvert::~AudioConvert()
{
    swr_free(&this->swrContext);

    av_freep(&this->buffer[0]);

}

int AudioConvert::allocContextSamples(int nb_samples)
{
    if(!this->invalidated)
    {
        this->invalidated = true;

        return av_samples_alloc(this->buffer, nullptr, this->out_channels,
                                nb_samples, this->out_sample_fmt, 0);
    }


    return 0;
}

int AudioConvert::convertAudio(AVFrame *frame)
{
    int len = swr_convert(this->swrContext, this->buffer, frame->nb_samples,
                          (const uint8_t **) frame->extended_data, frame->nb_samples);

    this->bufferLen  =  this->out_channels * len * av_get_bytes_per_sample(this->out_sample_fmt);

    return this->bufferLen;
}
