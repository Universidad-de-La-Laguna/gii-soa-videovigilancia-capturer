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
            this, SLOT(showFrame(const QRect&)));

    // Conexiones para el control de reproducción
    connect(ui->pbIniciar, SIGNAL(clicked()),
            movie_, SLOT(start()));
    connect(ui->pbParar, SIGNAL(clicked()),
            movie_, SLOT(stop()));
    connect(movie_, SIGNAL(stateChanged(QMovie::MovieState)),
            this, SLOT(movieStateChanged(QMovie::MovieState)));

    // Estado inicial de los botones de reproducción
    ui->pbIniciar->setDisabled(false);
    ui->pbParar->setDisabled(true);
    ui->pbPausar->setDisabled(true);
}

ImageViewerWindow::~ImageViewerWindow()
{
    movie_->deleteLater();
    delete ui;
}

void ImageViewerWindow::on_pbSalir_clicked()
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
        if (ui->cbAutoInicio->isChecked()) {
            movie_->start();
        }
//        QWaitCondition sleep;
//        QMutex mutex;
//        mutex.lock();               // Bloquear antes de que wait() lo libere
//        sleep.wait(&mutex, 5000);   // Espera de 5 segundos
//        mutex.unlock();
    }
}

void ImageViewerWindow::showFrame(const QRect&)
{
    ui->image->setPixmap(movie_->currentPixmap());
}

void ImageViewerWindow::on_pbPausar_clicked()
{
    if (movie_->state() == QMovie::Paused) {
        movie_->setPaused(false);
        ui->pbPausar->setText("Pausar");
    }
    else if (movie_->state() == QMovie::Running) {
        movie_->setPaused(true);
        ui->pbPausar->setText("Continuar");
    }
}

void ImageViewerWindow::movieStateChanged(QMovie::MovieState state)
{
    switch (state) {
    case QMovie::NotRunning:
        ui->pbIniciar->setDisabled(false);
        ui->pbParar->setDisabled(true);
        ui->pbPausar->setDisabled(true);
        break;
    case QMovie::Paused:
    case QMovie::Running:
        ui->pbIniciar->setDisabled(true);
        ui->pbParar->setDisabled(false);
        ui->pbPausar->setDisabled(false);
        break;
    }
}
