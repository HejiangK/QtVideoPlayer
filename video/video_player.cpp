//
// Created by 贺江 on 2017/9/8.
//

#include "video_player.h"

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent, 0)
{
    videoRender  = new VideoRender(this);

    videoRender->resize(size());

    audioRender = new AudioRender(this);

    videoRender->setAudio(audioRender);

}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::playPath(const QString &path)
{
    if(path.isEmpty())
    {
        QMessageBox messageBox(this);

        messageBox.setText("地址不能为空！");

        messageBox.show();

        messageBox.exec();

        return;
    }

    videoRender->begin();

    audioRender->begin();

    inputThread = new InputThread(this);

    inputThread->setPath(path);
    inputThread->setVideoDataContext(videoRender->getDataContext());
    inputThread->setAudioDataContext(audioRender->getDataContext());
    inputThread->begin();

}

void VideoPlayer::pause()
{

}

void VideoPlayer::stop()
{
    videoRender->finish();

    audioRender->finish();

    if(inputThread != nullptr)
    {
        inputThread->finish();

        inputThread->quit();

        inputThread = nullptr;
    }

}

void VideoPlayer::resizeEvent(QResizeEvent *event)
{
    videoRender->resize(size());
}
