//
// Created by 贺江 on 2017/8/4.
//

#include "image_cvt.h"

ImageConvert::ImageConvert(AVPixelFormat in_pixelFormat, int in_width, int in_height,
                                 AVPixelFormat out_pixelFormat, int out_width, int out_height)
{
    this->in_pixelFormat	= in_pixelFormat;
    this->out_pixelFormat	= out_pixelFormat;
    this->in_width			= in_width;
    this->in_height			= in_height;
    this->out_width			= out_width;
    this->out_height		= out_height;

    this->swsContext = sws_getContext(in_width, in_height, in_pixelFormat,
                                              out_width, out_height, out_pixelFormat,
                                              SWS_POINT, nullptr, nullptr, nullptr);
    this->frame		= av_frame_alloc();
    this->buffer	= (uint8_t*)av_malloc(avpicture_get_size(out_pixelFormat, out_width, out_height));

    avpicture_fill((AVPicture *)this->frame, this->buffer, out_pixelFormat, out_width, out_height);

}

ImageConvert::~ImageConvert()
{
    sws_freeContext(this->swsContext);
    av_frame_free(&this->frame);
}

void ImageConvert::convertImage(AVFrame *frame)
{
    sws_scale(this->swsContext, (const uint8_t *const *) frame->data, frame->linesize, 0,
              this->in_height, this->frame->data, this->frame->linesize);

    this->frame->width  = this->out_width;
    this->frame->height = this->out_height;
    this->frame->format = this->out_pixelFormat;
    this->frame->pts	= frame->pts;
}
