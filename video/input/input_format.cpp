//
// Created by 贺江 on 2017/8/31.
//

#include "input_format.h"

InputFormat::InputFormat()
{
    this->inputFormat       = nullptr;
    this->audioCodecContext = nullptr;
    this->videoCodecContext = nullptr;
    this->audioStream       = nullptr;
    this->videoStream       = nullptr;
    this->audioCodec        = nullptr;
    this->videoCodec        = nullptr;
    this->options           = nullptr;
    this->video_clock       = 0;
    this->audioIndex        = -1;
    this->videoIndex        = -1;
    this->synTime           = 0;

    this->formatContext = avformat_alloc_context();

    this->formatContext->use_wallclock_as_timestamps = 1;
    this->formatContext->interrupt_callback.callback = onStreamTimeOut;
    this->formatContext->interrupt_callback.opaque   = this;

    this->packet        = av_packet_alloc();
}

InputFormat::~InputFormat()
{
    if(this->formatContext != nullptr)
    {
        avformat_close_input(&this->formatContext);

        avformat_free_context(this->formatContext);
    }

    if(this->packet != nullptr)
    {
        av_packet_unref(this->packet);
        av_packet_free(&this->packet);
    }

    if(this->videoCodecContext != nullptr)
    {
        avcodec_free_context(&this->videoCodecContext);
    }

    if(this->audioCodecContext != nullptr)
    {
        avcodec_free_context(&this->audioCodecContext);
    }
}

int InputFormat::onStreamTimeOut(void *param)
{
    InputFormat *format = (InputFormat*)param;

    if (av_gettime() - format->getSynTime() > 1000 * 1000 * 10)
    {
        qDebug() << "input error !";
        return 1;
    }

    return 0;
}

void InputFormat::setOption(const char *key, const char *value)
{
    av_dict_set(&options, key, value, 0);
}

void InputFormat::setInputFormat(const char *format)
{
    this->inputFormat = av_find_input_format(format);
}

int InputFormat::openFormat(const char *path)
{
    setSynTime();

    if(avformat_open_input(&this->formatContext,path,this->inputFormat,&options) != 0)
        return -1;
    if(avformat_find_stream_info(this->formatContext, nullptr) != 0)
        return -1;
    return 0;
}

int InputFormat::openCodec(AVMediaType type)
{
    AVCodecContext *codecContext    = nullptr;
    AVCodec        *codec           = nullptr;
    AVStream       *stream          = nullptr;
    AVCodecID      codecID;
    for(int i = 0; i < this->formatContext->nb_streams; i ++)
    {
        if(this->formatContext->streams[i]->codecpar->codec_type == type)
        {
            codecContext = avcodec_alloc_context3(nullptr);
            stream       = this->formatContext->streams[i];
            codecID      = stream->codecpar->codec_id;

            avcodec_parameters_to_context(codecContext, stream->codecpar);
            av_codec_set_pkt_timebase(codecContext, stream->time_base);

            codec = avcodec_find_decoder(codecID);

            if(type == AVMEDIA_TYPE_VIDEO)
            {
                this->videoIndex        = i;
                this->videoCodecContext = codecContext;
                this->videoCodec        = codec;
                this->videoStream       = stream;
            }else if(type == AVMEDIA_TYPE_AUDIO)
            {
                this->audioIndex        = i;
                this->audioCodecContext = codecContext;
                this->audioCodec        = codec;
                this->audioStream       = stream;
            }

            if(codec == nullptr)
                return -1;
            if(avcodec_open2(codecContext,codec,nullptr) != 0)
                return -1;
            break;
        }
    }
    return 0;
}

AvFrameContext *InputFormat::readFrame()
{
    AVCodecContext  *codecContext;
    double          vpts;
    AvFrameContext     *frame = new AvFrameContext;

    setSynTime();

    if(av_read_frame(formatContext,packet) < 0)
        goto end;

    codecContext = packet->stream_index == audioIndex ? audioCodecContext : videoCodecContext;
    frame->type  = codecContext->codec_type;

    if(avcodec_send_packet(codecContext,packet)!= 0)
        goto end;

    if(avcodec_receive_frame(codecContext,frame->frame) != 0)
        goto end;

    if(frame->type == AVMEDIA_TYPE_VIDEO)
    {

        if ((vpts = av_frame_get_best_effort_timestamp(frame->frame)) == AV_NOPTS_VALUE)
            vpts = 0;

        vpts *= av_q2d(videoStream->time_base);


        frame->pts         = synchronize(frame->frame, vpts) * 1000000;;
        frame->pixelFormat = videoCodecContext->pix_fmt;
        frame->duration    = AV_TIME_BASE * videoStream->r_frame_rate.den / videoStream->r_frame_rate.num;

    } else
    {

        if (packet->pts != AV_NOPTS_VALUE)
            frame->pts   = av_q2d(audioStream->time_base) * packet->pts * 1000000;
        else
            frame->pts   = 0;

        frame->sampleFormat = audioCodecContext->sample_fmt;
        frame->sampleRate   = audioCodecContext->sample_rate;
        frame->channels     = audioCodecContext->channels;
        frame->duration     = AV_TIME_BASE * (1 / av_q2d({audioCodecContext->sample_rate, 1})) * frame->frame->nb_samples;

    }

    av_packet_unref(packet);

    return frame;

    end:

    delete frame;

    return nullptr;
}

double InputFormat::synchronize(AVFrame *srcFrame, double pts)
{
    double frame_delay;

    if (pts != 0)
        video_clock = pts;
    else
        pts = video_clock;

    frame_delay = av_q2d(videoStream->time_base);
    frame_delay += srcFrame->repeat_pict * (frame_delay * 0.5);

    video_clock += frame_delay;

    return pts;
}

void InputFormat::terminal()
{
    QMutexLocker locker(&mutex);

    synTime = 0;
}

void InputFormat::setSynTime()
{
    QMutexLocker locker(&mutex);

    synTime = av_gettime();
}

int64_t InputFormat::getSynTime()
{
    QMutexLocker locker(&mutex);

    return synTime;
}
