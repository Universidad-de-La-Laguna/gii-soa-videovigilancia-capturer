#include <QImage>
#include <QRect>
#include <QThread>
#include <QVector>

#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

#include "cvmatandqimage.h"
#include "motiondetector.h"

MotionDetector::MotionDetector()
    : backgroundSubtractor_(), stopRequested(false)
{
    backgroundSubtractor_.nmixtures = 3;
    backgroundSubtractor_.bShadowDetection = false;
    this->moveToThread(&workingThread_);
}

MotionDetector::~MotionDetector()
{
    stop();
}

void MotionDetector::start()
{
    workingThread_.start();
}

void MotionDetector::stop()
{
    stopRequested = true;
    workingThread_.exit();
    workingThread_.wait();
}

void MotionDetector::doTask(const QImage& frame)
{
    typedef std::vector<std::vector<cv::Point> > ContoursType;

    if (stopRequested)
        return;

    cv::Mat image = QtOcv::image2Mat(frame, CV_8UC(3));
    cv::Mat foregroundMask;
    ContoursType contours;
    QVector<QRect> boundingBoxes;

    backgroundSubtractor_(image, foregroundMask);
    cv::erode(foregroundMask, foregroundMask, cv::Mat());
    cv::dilate(foregroundMask, foregroundMask, cv::Mat());
    cv::findContours(foregroundMask, contours, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE);

    if (! contours.empty()) {
        for (ContoursType::const_iterator i = contours.begin();
             i < contours.end(); ++i)
        {
            cv::Rect rect = cv::boundingRect(*i);
            boundingBoxes.prepend(QRect(rect.x, rect.y, rect.width, rect.height));
        }

        emit done(frame, boundingBoxes);
    }
}
