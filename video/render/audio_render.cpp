//
// Created by 贺江 on 2017/9/9.
//

#include "audio_render.h"

AudioRender::AudioRender(QObject *parent) : QObject(parent)
{
    audioOutput     = nullptr;
    audioThread     = nullptr;
    outputBuffer    = nullptr;
    curPts             = 0;

    audioFormat.setSampleRate(44100);
    audioFormat.setChannelCount(2);
    audioFormat.setSampleSize(16);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
}

AudioRender::~AudioRender()
{

}

void AudioRender::begin()
{
    if(audioOutput == nullptr)
    {
        QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

        if(info.isFormatSupported(audioFormat))
        {
            audioOutput = new QAudioOutput(info,audioFormat);
            audioOutput->setBufferSize(1024 * 100);

            outputBuffer = audioOutput->start();
        }
    }

    if(audioThread == nullptr)
    {
        audioThread = new AudioThread(this);

        audioThread->setAudioFormat(AV_SAMPLE_FMT_S16,44100,2);
        audioThread->start();

        connect(audioThread,&AudioThread::onAudioData,this,&AudioRender::onAudioData,Qt::DirectConnection);
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

void AudioRender::onAudioData(quint8 *buffer, int length, qint64 pts)
{
    this->curPts = pts;

    outputBuffer->write((char*)buffer,length);
}

DataContext *AudioRender::getDataContext()
{
    if(audioThread == nullptr)
        return nullptr;

    return audioThread->getDataContext();
}

int64_t AudioRender::getCurAudioTime()
{

    int64_t size = audioOutput->bufferSize() - outputBuffer->bytesAvailable();

    int bytes_per_sec = 44100 *2 * 2;

    int64_t pts = this->curPts - static_cast<double>(size) / bytes_per_sec * 1000000;
    
    return pts;
}
