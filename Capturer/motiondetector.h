#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <QObject>
#include <QRect>

class MotionDetector : public QObject
{
    Q_OBJECT
    
signals:
    void done(const QImage&, const QVector<QRect>&);
    
public slots:
    void doTask(const QImage&);
};

#endif // MOTIONDETECTOR_H
