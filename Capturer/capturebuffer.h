#ifndef CAPTUREBUFFER_H
#define CAPTUREBUFFER_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>

class CaptureBuffer : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    explicit CaptureBuffer(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType =
            QAbstractVideoBuffer::NoHandle) const;

    bool present(const QVideoFrame &frame);

    QImage currentImage() const;

    QPixmap currentPixmap() const;

signals:
    void updated(const QRect&);

private:
    QImage lastFrame_;
};

#endif // CAPTUREBUFFER_H
