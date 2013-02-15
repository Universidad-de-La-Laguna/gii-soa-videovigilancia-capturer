#include <QFile>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QPixmap>

#include "imageviewerwindow.h"
#include "ui_imageviewerwindow.h"

ImageViewerWindow::ImageViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerWindow)
{
    ui->setupUi(this);
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
            QString(), tr("Imagen JPEG (*.jpg *.jpeg)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("No se puede abrir el archivo"));
            return;
        }
        // QPixmap pixmap(fileName);
        QImageReader imagereader(&file);
        QPixmap pixmap = QPixmap::fromImageReader(&imagereader);
        ui->image->setPixmap(pixmap);
        file.close();
    }
}
