#include <QList>
#include <QVideoFrame>
#include <QPixmap>

#include "capturebuffer.h"

CaptureBuffer::CaptureBuffer(QObject *parent)
    : QAbstractVideoSurface(parent)
{
}

QList<QVideoFrame::PixelFormat> CaptureBuffer::supportedPixelFormats(
    QAbstractVideoBuffer::HandleType) const
{
    // Debemos devolver los formatos que soportamos. Nos sirven todos los
    // de QImage porque es lo que usaremos en present()
    QList<QVideoFrame::PixelFormat> formats;
    formats << QVideoFrame::Format_ARGB32;
    formats << QVideoFrame::Format_ARGB32_Premultiplied;
    formats << QVideoFrame::Format_RGB32;
    formats << QVideoFrame::Format_RGB24;
    formats << QVideoFrame::Format_RGB565;
    formats << QVideoFrame::Format_RGB555;
    return formats;
}

bool CaptureBuffer::present(const QVideoFrame &frame)
{
    QVideoFrame tempFrame = frame;

    // Nos han pasado un frame para mostrarlo. Vamos a convertirlo
    // a QImage y a guardarlo.
    tempFrame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat =
            QVideoFrame::imageFormatFromPixelFormat(tempFrame.pixelFormat());
    QImage frameAsImage = QImage(tempFrame.bits(), tempFrame.width(),
                                 tempFrame.height(), tempFrame.bytesPerLine(),
                                 imageFormat);
    lastFrame_ = frameAsImage.copy();
    tempFrame.unmap();

    emit updated(QRect());
    return true;
}

QImage CaptureBuffer::currentImage() const
{
    return lastFrame_;
}

QPixmap CaptureBuffer::currentPixmap() const
{
    return QPixmap::fromImage(lastFrame_);
}
