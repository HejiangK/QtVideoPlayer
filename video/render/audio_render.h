//
// Created by 贺江 on 2017/9/9.
//

#ifndef QTVIDEOPLAYER_AUDIO_RENDER_H
#define QTVIDEOPLAYER_AUDIO_RENDER_H

#include <QObject>

#include "audio_thread.h"

class AudioRender : public QObject
{
public:
    AudioRender(QObject *parent);

    virtual ~AudioRender();

    void begin();

    void finish();

    DataContext *getDataContext();

protected slots:

    void onAudioData(uint8_t *buffer,int length,int64_t pts);

private:

    AudioThread     *audioThread;

};


#endif //QTVIDEOPLAYER_AUDIO_RENDER_H
