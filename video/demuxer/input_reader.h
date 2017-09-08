//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_VIDEO_CAPTURE_H
#define QTVIDEOPLAYER_VIDEO_CAPTURE_H

#include <QThread>

#include "avformat.h"

class InputReader : public QThread
{
    Q_OBJECT
public:
    InputReader(QObject *parent);

    virtual ~InputReader();

    void setPath(const QString &path);

    void setVideoDataContext(DataContext *videoDataContext);

    void setAudioDataContext(DataContext *audioDataContext);

    void begin();

    void finish();

    signals:

    void onOpenError();

    void onError();

    void onComplete();

protected:

    void run() override;

private:

    AvFormat        *avFormat;

    char            path[512];

    DataContext     *videoDataContext;

    DataContext     *audioDataContext;

};


#endif //QTVIDEOPLAYER_VIDEO_CAPTURE_H
