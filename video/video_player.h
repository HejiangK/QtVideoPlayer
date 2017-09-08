//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_VIDEO_PLAYER_H
#define QTVIDEOPLAYER_VIDEO_PLAYER_H

#include <QWidget>
#include <QPainter>
#include <QMessageBox>

#include "video/render/audio_thread.h"
#include "video/render/video_thread.h"
#include "video/demuxer/input_reader.h"

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

    void onAudioData(uint8_t *buffer,int length,int64_t pts);

    void onVideoFrame(const QImage &frame);

protected:

    void paintEvent(QPaintEvent *event) override;

private:

    QImage          curFrame;

    VideoThread     *videoThread;

    AudioThread     *audioThread;

    InputReader     *inputReader;

};


#endif //QTVIDEOPLAYER_VIDEO_PLAYER_H
