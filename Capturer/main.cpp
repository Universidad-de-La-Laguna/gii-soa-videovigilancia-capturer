#include "imageviewerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Información cerca de la aplicación usada por QSettings
    QCoreApplication::setOrganizationName("Jesus Torres");
//    QCoreApplication::setOrganizationDomain("jmtorres.webs.ull.es");
    QCoreApplication::setApplicationName("Visor de MJPEG");

    ImageViewerWindow w;
    w.show();
    
    return a.exec();
}
