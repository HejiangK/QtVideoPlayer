//
// Created by 贺江 on 2017/9/8.
//

#ifndef QTVIDEOPLAYER_MAIN_WINDOW_H
#define QTVIDEOPLAYER_MAIN_WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

#include "video_player.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr);

    virtual ~MainWindow();

private:

    VideoPlayer     *videoPlayer;

    QVBoxLayout     *mainLayout;

    QHBoxLayout     *toolLayout;

    QTextEdit       *addressTextBox;

    QPushButton     *btnPlay;

    QPushButton     *btnStop;

};


#endif //QTVIDEOPLAYER_MAIN_WINDOW_H
