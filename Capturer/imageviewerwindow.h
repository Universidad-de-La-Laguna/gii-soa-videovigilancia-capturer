#ifndef IMAGEVIEWERWINDOW_H
#define IMAGEVIEWERWINDOW_H

#include <QImage>
#include <QMovie>
#include <QMainWindow>
#include <QRect>
#include <QVector>

#include "motiondetector.h"

namespace Ui {
class ImageViewerWindow;
}

class ImageViewerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImageViewerWindow(QWidget *parent = 0);
    ~ImageViewerWindow();

signals:
    void motionDetectionRequested(const QImage&);

private slots:
    void on_pushButton_clicked();

    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

    void on_movie_updated(const QRect&);

    void on_motionDetector_done(const QImage&, const QVector<QRect>&);

private:
    Ui::ImageViewerWindow *ui;
    QMovie *movie_;
    MotionDetector motionDetector_;
};

#endif // IMAGEVIEWERWINDOW_H
