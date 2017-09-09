//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_VIDEO_RENDER_THREAD_H
#define QTVIDEOPLAYER_VIDEO_RENDER_THREAD_H

#include <QThread>
#include <QSize>
#include <QImage>

#include "video/data/data_context.h"
#include "video/data/image_cvt.h"
#include "audio_render.h"

class VideoThread : public QThread
{
    Q_OBJECT
public:
    VideoThread(QObject *parent);

    virtual ~VideoThread();

    void setSize(const QSize &size);

    DataContext *getDataContext();

    void setAudio(AudioRender *audioRender);

signals:

    void onFrame(const QImage &frame);

protected:
    void run() override;

private:

    DataContext         *dataContext;

    QSize               size;

    AudioRender         *audioRender;

};


#endif //QTVIDEOPLAYER_VIDEO_RENDER_THREAD_H
