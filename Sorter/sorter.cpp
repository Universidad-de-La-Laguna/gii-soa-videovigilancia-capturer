#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVector>

#include "sorter.h"

Sorter::Sorter() : QObject()
{
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    // Registrar los parámetros de la señales. Necesitamos registrar
    // QList<int> porque no es un tipo conocido por el sistema de
    // meta-objetos de Qt.
    qRegisterMetaType< QVector<int> >("QVector<int>");

    // Pasar la petición de ordenar a la instancia de SorterWorker
    connect(this, SIGNAL(sortingRequested(QVector<int>)),
        &sorterWorker_, SLOT(doSort(QVector<int>)));
    // Ser notificado cuando el vector haya sido ordenado
    connect(&sorterWorker_, SIGNAL(vectorSorted(QVector<int>)),
        this, SLOT(vectorSorted(QVector<int>)));

    // Migrar la instancia de SorterWorker al hilo de trabajo
    sorterWorker_.moveToThread(&workingThread_);

    // Iniciar el hilo de trabajo
    workingThread_.start();
}

void Sorter::sortAsync(const QVector<int>& list)
{
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

    emit sortingRequested(list);
}

void Sorter::vectorSorted(const QVector<int>& list)
{
    qDebug() << list;
}
