#include <QCoreApplication>

#include "sorter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Sorter sorter;
    sorter.sortAsync(QVector<int>() << 1 << 3 << 2);

    return a.exec();
}
