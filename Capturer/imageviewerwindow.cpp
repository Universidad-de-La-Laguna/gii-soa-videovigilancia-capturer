#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QMutex>
#include <QPixmap>
#include <QSettings>
#include <QWaitCondition>

#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"
#include "acercadedialog.h"
#include "preferencesdialog.h"

ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);

    QSettings settings;

    // Reproducción de archivos MPJEG
    movie_ = new QMovie(this);
//    ui->label->setMovie(movie_);
    connect(movie_, SIGNAL(updated(const QRect&)),
            this, SLOT(showFrame(const QRect&)));

    // Reproducción de imágenes de la webcam
    QString device = settings.value("capturer/dispositivo").toString();
    if (device.isEmpty()) {
        camera_ = new QCamera(this);
    }
    else {
        camera_ = new QCamera(device.toLocal8Bit(), this);
    }
    captureBuffer_ = new CaptureBuffer(this);
    camera_->setViewfinder(captureBuffer_);
    connect(captureBuffer_, SIGNAL(updated(const QRect&)),
            this, SLOT(showFrame(const QRect&)));

    // Conexiones para el control de reproducción
    connect(ui->pbIniciar, SIGNAL(clicked()),
            movie_, SLOT(start()));
    connect(ui->pbParar, SIGNAL(clicked()),
            movie_, SLOT(stop()));
    connect(movie_, SIGNAL(stateChanged(QMovie::MovieState)),
            this, SLOT(movieStateChanged(QMovie::MovieState)));

    // Estado inicial de los botones de reproducción
    ui->cbAutoInicio->setChecked(settings.value("viewer/autoinicio", false).toBool());
    ui->pbIniciar->setDisabled(true);
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

    if (fileName.isEmpty()) {
        return;
    }

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

    camera_->stop();
    if (ui->cbAutoInicio->isChecked()) {
        movie_->start();
    }
    else {
        ui->pbIniciar->setDisabled(false);
    }

//        QWaitCondition sleep;
//        QMutex mutex;
//        mutex.lock();               // Bloquear antes de que wait() lo libere
//        sleep.wait(&mutex, 5000);   // Espera de 5 segundos
//        mutex.unlock();
}

void ImageViewerWindow::showFrame(const QRect&)
{
    if (movie_->state() == QMovie::Running) {
        ui->image->setPixmap(movie_->currentPixmap());
    }
    else if (camera_->state() == QCamera::ActiveState) {
        ui->image->setPixmap(captureBuffer_->currentPixmap());
    }
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

void ImageViewerWindow::on_cbAutoInicio_stateChanged(int arg1)
{
    QSettings settings;
    settings.setValue("viewer/autoinicio", arg1==Qt::Checked);
}

void ImageViewerWindow::on_actionAcerca_de_triggered()
{
    AcercaDeDialog dialog(this);
    dialog.exec();
}

void ImageViewerWindow::on_actionCapturar_triggered()
{
    movie_->stop();
    ui->pbIniciar->setDisabled(true);
    camera_->start();
}

void ImageViewerWindow::on_actionPreferencias_triggered()
{
    PreferencesDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QSettings settings;
        QString currentDevice = settings.value("capturer/dispositivo").toString();
        QString selectedDevice = dialog.selectedDevice();
        if (selectedDevice != currentDevice) {
            settings.setValue("capturer/dispositivo", selectedDevice);
            camera_->stop();
            camera_->deleteLater();
            if (selectedDevice.isEmpty()) {
                camera_ = new QCamera(this);
                camera_->setViewfinder(captureBuffer_);
            }
            else {
                camera_ = new QCamera(selectedDevice.toLocal8Bit(), this);
                camera_->setViewfinder(captureBuffer_);
            }
        }
   }
}
