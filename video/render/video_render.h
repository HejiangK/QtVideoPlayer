//
// Created by 贺江 on 2017/9/9.
//

#ifndef QTVIDEOPLAYER_VIDEO_RENDER_H
#define QTVIDEOPLAYER_VIDEO_RENDER_H

#include <QWidget>
#include <QImage>
#include <QPainter>

#include "video_thread.h"

class VideoRender : public QWidget
{
public:
    VideoRender(QWidget *parent);

    virtual ~VideoRender();

    void begin();

    void finish();

    DataContext *getDataContext();

protected slots:

    void onFrame(const QImage &frame);

protected:

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:

    QImage          frame;

    VideoThread     *videoThread;

};


#endif //QTVIDEOPLAYER_VIDEO_RENDER_H
