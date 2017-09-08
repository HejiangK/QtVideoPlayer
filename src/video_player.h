//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_VIDEO_PLAYER_H
#define QTVIDEOPLAYER_VIDEO_PLAYER_H

#include <QWidget>
#include <QPainter>


class VideoPlayer : public QWidget
{
public:
    VideoPlayer(QWidget *parent);

    virtual ~VideoPlayer();

protected:
    
    void paintEvent(QPaintEvent *event) override;

};


#endif //QTVIDEOPLAYER_VIDEO_PLAYER_H
