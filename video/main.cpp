#include <iostream>

#include <QApplication>

#include "main_window.h"

extern "C"
{
#include <libavdevice/avdevice.h>
};

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    av_register_all();
    avformat_network_init();
    avdevice_register_all();

    MainWindow  window;

    window.setMinimumSize(640,500);

    window.show();

    return app.exec();
}