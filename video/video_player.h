//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_VIDEO_PLAYER_H
#define QTVIDEOPLAYER_VIDEO_PLAYER_H

#include <QWidget>
#include <QPainter>
#include <QMessageBox>

#include "video/render/audio_render.h"
#include "video/render/video_render.h"
#include "video/input/input_thread.h"

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent);

    virtual ~VideoPlayer();

    void playPath(const QString &path);

    void pause();

    void stop();

protected slots:

    void resizeEvent(QResizeEvent *event) override;

private:

    VideoRender     *videoRender;

    AudioRender     *audioRender;

    InputThread     *inputThread;

};


#endif //QTVIDEOPLAYER_VIDEO_PLAYER_H
