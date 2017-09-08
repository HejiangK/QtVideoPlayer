//
// Created by 贺江 on 2017/9/8.
//

#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent, 0)
{
    mainLayout = new QVBoxLayout(this);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    videoPlayer = new VideoPlayer(this);

    videoPlayer->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    videoPlayer->setMinimumSize(this->width(),480);
    mainLayout->addWidget(videoPlayer);

    toolLayout = new QHBoxLayout(this);

    toolLayout->setMargin(0);
    toolLayout->setSpacing(10);

    addressTextBox = new QTextEdit(this);

    addressTextBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    addressTextBox->setMinimumSize(0,25);

    btnPlay = new QPushButton(this);

    btnPlay->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    btnPlay->setMinimumSize(30,0);
    btnPlay->setText("播放");
    btnPlay->installEventFilter(this);

    btnStop = new QPushButton(this);

    btnStop->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    btnStop->setMinimumSize(30,0);
    btnStop->setText("停止");
    btnStop->installEventFilter(this);

    toolLayout->addWidget(addressTextBox);
    toolLayout->addWidget(btnPlay);
    toolLayout->addWidget(btnStop);

    mainLayout->addLayout(toolLayout);

}

MainWindow::~MainWindow()
{

}
