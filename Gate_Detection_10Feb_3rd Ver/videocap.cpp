#include "videocap.h"

#include <qthread.h>


VideoCap::VideoCap(QObject *parent)
{


    QThread *th =new QThread();
    connect(th, SIGNAL(started()), this, SLOT(sl_startTimer()));
    cap =new VideoCapture(/*"/home/kimia/Desktop/FIRA_Pix/sample.mp4"*/);
    cap->set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,240);
    timer =new QTimer();
    moveToThread(th);
    timer->moveToThread(th);
    connect(timer,SIGNAL(timeout()),this,SLOT(receiveFrame()),Qt::DirectConnection);
    QMetaObject::invokeMethod(this, "sl_startTimer", Qt::QueuedConnection);

    th->start();
}


bool VideoCap::openCamera(int port)
{


    if(cap->open(port))
        return true;

    return false;
}

void VideoCap::receiveFrame()
{

    *cap>>frame;
    //qDebug("frame got");
    emit sendFrame(frame);
}

void VideoCap::sl_startTimer()
{
    timer->start(2);
}
