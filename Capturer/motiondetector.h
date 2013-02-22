#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <QObject>
#include <QRect>
#include <QThread>

#include <opencv2/video/video.hpp>

class MotionDetector : public QObject
{
    Q_OBJECT

public:
    MotionDetector();
    ~MotionDetector();

    void start();
    void stop();

signals:
    void done(const QImage&, const QVector<QRect>&);
    
public slots:
    void doTask(const QImage&);

private:
    QThread workingThread_;
    cv::BackgroundSubtractorMOG2 backgroundSubtractor_;
    bool stopRequested;
};

#endif // MOTIONDETECTOR_H
