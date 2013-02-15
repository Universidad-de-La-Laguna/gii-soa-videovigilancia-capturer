#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QMutex>
#include <QPixmap>
#include <QWaitCondition>

#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"

ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);

    movie_ = new QMovie();
//    ui->label->setMovie(movie_);
    connect(movie_, SIGNAL(updated(const QRect&)),
            this, SLOT(on_movie_updated(const QRect&)));
}

ImageViewerWindow::~ImageViewerWindow()
{
    delete ui;
}

void ImageViewerWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void ImageViewerWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void ImageViewerWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir el archivo"),
            QString(), tr("Vídeo MJPEG (*.mjpg *.mjpeg)"));

    if (!fileName.isEmpty()) {
        movie_->setFileName(fileName);
        if (!movie_->isValid()) {
            if (!movie_->device()->isOpen()) {
                QMessageBox::critical(this, tr("Error"), tr("No se puede abrir el archivo"));
            }
            else {
                QMessageBox::critical(this, tr("Error"), tr("El formato no es válido"));
            }
            return;
        }
        movie_->start();
//        QWaitCondition sleep;
//        QMutex mutex;
//        sleep.wait(&mutex, 2000);   // Espera de 2 segundos
    }
}

void ImageViewerWindow::on_movie_updated(const QRect&)
{
    ui->image->setPixmap(movie_->currentPixmap());
}
