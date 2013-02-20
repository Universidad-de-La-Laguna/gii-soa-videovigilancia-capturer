#include <QImage>
#include <QRect>
#include <QVector>

#include "motiondetector.h"

void MotionDetector::doTask(const QImage& image)
{
    QVector<QRect> boudingBoxes;
    emit done(image, boudingBoxes);
}
