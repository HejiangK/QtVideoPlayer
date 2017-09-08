//
// Created by 贺江 on 2017/9/8.
//

#include "input_reader.h"

InputReader::InputReader(QObject *parent) : QThread(parent)
{
    avFormat         = nullptr;
    videoDataContext = nullptr;
    audioDataContext = nullptr;
}

InputReader::~InputReader()
{
    if(avFormat != nullptr)
        delete avFormat;

    avFormat = nullptr;
}

void InputReader::setPath(const QString &path)
{
    sprintf(this->path,"%s",path.toLatin1().data());
}

void InputReader::setVideoDataContext(DataContext *videoDataContext)
{
    this->videoDataContext = videoDataContext;
}

void InputReader::setAudioDataContext(DataContext *audioDataContext)
{
    this->audioDataContext  = audioDataContext;
}

void InputReader::begin()
{
    this->start();
}

void InputReader::finish()
{
    this->requestInterruption();
    this->quit();
}

void InputReader::run()
{
    avFormat = new AvFormat();

    if(avFormat->openFormat(path) < 0)
    {
        onOpenError();

        return;
    }

    if(avFormat->openCodec(AVMEDIA_TYPE_VIDEO) < 0)
    {
        onOpenError();

        return;
    }

    if(avFormat->openCodec(AVMEDIA_TYPE_AUDIO) < 0)
    {
        onOpenError();

        return;
    }

    while (!isInterruptionRequested())
    {
        AvFrameContext *frame = avFormat->readFrame();

        if(frame == nullptr)
        {
            onError();

            continue;
        }

        if(frame->type == AVMEDIA_TYPE_VIDEO)
            videoDataContext->addFrame(frame);
        else if(frame->type == AVMEDIA_TYPE_AUDIO)
            audioDataContext->addFrame(frame);

        if(videoDataContext->getBufferLength() > 50000000)
            sleep(1);

    }

}
