//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_AUDIO_RENDER_THREAD_H
#define QTVIDEOPLAYER_AUDIO_RENDER_THREAD_H

#include <QThread>

#include "video/data/data_context.h"
#include "video/data/audio_cvt.h"

class AudioThread : public QThread
{
    Q_OBJECT
public:
    AudioThread(QObject *parent);

    virtual ~AudioThread();

    void setAudioFormat(AVSampleFormat sampleFormat,int sampleRate,int channels);

    DataContext *getDataContext();

signals:

    void onAudioData(uint8_t *buffer,int length,int64_t pts);

protected:
    void run() override;

private:

    DataContext         *dataContext;

    AVSampleFormat      sampleFormat;

    int                 sampleRate;

    int                 channels;

};


#endif //QTVIDEOPLAYER_AUDIO_RENDER_THREAD_H
