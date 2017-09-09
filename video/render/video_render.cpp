//
// Created by 贺江 on 2017/9/9.
//

#include "video_render.h"

VideoRender::VideoRender(QWidget *parent) : QWidget(parent, 0)
{
    videoThread = nullptr;
}

VideoRender::~VideoRender()
{

}

void VideoRender::begin()
{
    if(videoThread == nullptr)
    {
        videoThread = new VideoThread(this);

        videoThread->setSize(size());

        connect(videoThread, &VideoThread::onFrame,this,&VideoRender::onFrame,Qt::DirectConnection);
    }

}

void VideoRender::finish()
{
    if(videoThread != nullptr)
    {
        disconnect(videoThread, &VideoThread::onFrame,this,&VideoRender::onFrame);

        videoThread->requestInterruption();
        videoThread->quit();
        videoThread = nullptr;
    }
}

DataContext *VideoRender::getDataContext()
{
    if(videoThread == nullptr)
        return nullptr;

    return videoThread->getDataContext();
}

void VideoRender::resizeEvent(QResizeEvent *event)
{
    if(videoThread != nullptr)
        videoThread->setSize(size());
}

void VideoRender::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QColor(0xcccccc));

    painter.drawRect(0,0,this->width(),this->height());

    if(!frame.isNull())
    {
        painter.drawImage(QPoint(0,0),frame);
    }
}

void VideoRender::onFrame(const QImage &frame)
{
    this->frame = frame;
}
