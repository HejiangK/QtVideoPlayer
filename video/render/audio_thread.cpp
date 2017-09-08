//
// Created by 贺江 on 2017/9/8.
//

#include "audio_thread.h"

AudioThread::AudioThread(QObject *parent) : QThread(parent)
{
    dataContext = new DataContext();
}

AudioThread::~AudioThread()
{

}

void AudioThread::setAudioFormat(AVSampleFormat sampleFormat, int sampleRate, int channels)
{
    this->sampleFormat  = sampleFormat;
    this->sampleRate    = sampleRate;
    this->channels      = channels;
}

DataContext *AudioThread::getDataContext()
{
    return dataContext;
}

void AudioThread::run()
{
    AudioConvert    *audioConvert   = nullptr;
    AvFrameContext  *frame          = nullptr;
    int64_t         pts;

    while (!isInterruptionRequested())
    {
        frame = dataContext->getFrame();

        if(audioConvert == nullptr)
            audioConvert = new AudioConvert(frame->sampleFormat, frame->sampleRate, frame->channels,
                                               this->sampleFormat, this->sampleRate, this->channels);

        if(audioConvert->allocContextSamples(frame->frame->nb_samples) < 0)
        {
            break;
        }

        if(audioConvert->convertAudio(frame->frame) < 0)
        {
            break;
        }

        pts = frame->pts;

        pts += audioConvert->bufferLen / (2 * this->channels * this->sampleRate);

        onAudioData(*audioConvert->buffer,audioConvert->bufferLen,pts);

        delete frame;

    }
}
