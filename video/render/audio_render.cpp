//
// Created by 贺江 on 2017/9/9.
//

#include "audio_render.h"

AudioRender::AudioRender(QObject *parent) : QObject(parent)
{
    audioThread = nullptr;
}

AudioRender::~AudioRender()
{

}

void AudioRender::begin()
{
    if(audioThread == nullptr)
    {
        audioThread = new AudioThread(this);

        audioThread->setAudioFormat(AV_SAMPLE_FMT_S16,44100,2);
        audioThread->start();

        connect(audioThread,&AudioThread::onAudioData,this,&AudioRender::onAudioData);
    }

}

void AudioRender::finish()
{
    if (audioThread != nullptr)
    {
        disconnect(audioThread,&AudioThread::onAudioData,this,&AudioRender::onAudioData);

        audioThread->requestInterruption();
        audioThread->quit();

        audioThread = nullptr;
    }
}

void AudioRender::onAudioData(uint8_t *buffer, int length, int64_t pts)
{

}

DataContext *AudioRender::getDataContext()
{
    if(audioThread == nullptr)
        return nullptr;

    return audioThread->getDataContext();
}
