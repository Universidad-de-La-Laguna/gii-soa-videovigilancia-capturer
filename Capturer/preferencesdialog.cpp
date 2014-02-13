#include "QCamera"
#include "QSettings"

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    QSettings settings;

    // Añadir elementos al combo de elección de dispositivo
    ui->cbDispositivo->addItem("Predeterminado", "");
    foreach(QByteArray device, QCamera::availableDevices()) {
        ui->cbDispositivo->addItem(QCamera::deviceDescription(device), device);
    }

    // Seleccionar el dispositivo actual en el combo
    QString currentDevice = settings.value("capturer/dispositivo").toString();
    if (! currentDevice.isEmpty()) {
        QString description = QCamera::deviceDescription(currentDevice.toLocal8Bit());
        ui->cbDispositivo->setCurrentText(description);
    }
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

QString PreferencesDialog::selectedDevice() const
{
    return ui->cbDispositivo->currentData().toString();
}
