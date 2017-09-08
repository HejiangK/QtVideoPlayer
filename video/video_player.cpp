//
// Created by 贺江 on 2017/9/8.
//

#include "video_player.h"

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent, 0)
{

}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QColor(0xcccccc));

    painter.drawRect(0,0,this->width(),this->height());

    if(!curFrame.isNull())
    {
        painter.drawImage(QPoint(0,0),curFrame);
    }

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


    audioThread = new AudioThread(this);

    audioThread->setAudioFormat(AV_SAMPLE_FMT_S16,44100,2);
    audioThread->start();

    videoThread = new VideoThread(this);

    videoThread->setSize(this->size());
    videoThread->start();

    inputReader = new InputReader(this);

    inputReader->setPath(path);
    inputReader->setVideoDataContext(videoThread->getDataContext());
    inputReader->setAudioDataContext(audioThread->getDataContext());
    inputReader->start();

    connect(videoThread,&VideoThread::renderFrame,this,&VideoPlayer::onVideoFrame,Qt::DirectConnection);
    connect(audioThread,&AudioThread::onAudioData,this,&VideoPlayer::onAudioData,Qt::DirectConnection);

}

void VideoPlayer::pause()
{

}

void VideoPlayer::stop()
{

}

void VideoPlayer::onVideoFrame(const QImage &frame)
{
    curFrame = frame.copy();

    update();
}

void VideoPlayer::onAudioData(uint8_t *buffer, int length, int64_t pts)
{

}
