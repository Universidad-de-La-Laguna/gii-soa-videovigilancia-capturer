#ifndef IMAGEVIEWERWINDOW_H
#define IMAGEVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ImageViewerWindow;
}

class ImageViewerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ImageViewerWindow(QWidget *parent = 0);
    ~ImageViewerWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

private:
    Ui::ImageViewerWindow *ui;
};

#endif // IMAGEVIEWERWINDOW_H
