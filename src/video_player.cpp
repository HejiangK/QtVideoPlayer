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

    painter.setBrush(QColor(0xcccccc));

    painter.drawRect(0,0,this->width(),this->height());

}
