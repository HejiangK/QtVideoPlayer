//
// Created by 贺江 on 2017/9/9.
//

#ifndef QTVIDEOPLAYER_AUDIO_RENDER_H
#define QTVIDEOPLAYER_AUDIO_RENDER_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioOutput>

#include "audio_thread.h"

class AudioRender : public QObject
{
public:
    AudioRender(QObject *parent);

    virtual ~AudioRender();

    void begin();

    void finish();

    DataContext *getDataContext();

    int64_t getCurAudioTime();

protected slots:

    void onAudioData(quint8 *buffer,int length,qint64 pts);

private:

    AudioThread     *audioThread;

    QAudioFormat    audioFormat;

    QAudioOutput    *audioOutput;

    QIODevice       *outputBuffer;

    int64_t         curPts;

};


#endif //QTVIDEOPLAYER_AUDIO_RENDER_H
