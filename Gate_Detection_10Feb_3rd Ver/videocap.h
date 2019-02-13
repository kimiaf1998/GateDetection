#ifndef VIDEOCAP_H
#define VIDEOCAP_H

#include <opencv2/opencv.hpp>

#include <QObject>
#include <QTimer>
using namespace cv;

class VideoCap : public QObject
{
    Q_OBJECT
public:
    VideoCap(QObject *parent = 0);
    bool openCamera(int port);

private:
    Mat frame;
    QTimer *timer;
    VideoCapture *cap;
signals:
    void sendFrame(Mat frame);
 public slots:
    void receiveFrame();
    void sl_startTimer();
};

#endif // VIDEOCAP_H
