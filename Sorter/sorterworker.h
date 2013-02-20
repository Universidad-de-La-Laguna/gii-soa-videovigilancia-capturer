#ifndef SORTERWORKER_H
#define SORTERWORKER_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVector>

class SorterWorker : public QObject
{
    Q_OBJECT

    signals:
        // Señal emitida cuando el vector ha sido ordenado
        void vectorSorted(const QVector<int> &list);

    public slots:
        // Método encargado del ordenamiento
        void doSort(const QVector<int> &list) {
            qDebug() << Q_FUNC_INFO << QThread::currentThreadId();

            QVector<int> list_sorted = list;
            qSort(list_sorted);
            emit vectorSorted(list_sorted);
        }
};

#endif // SORTERWORKER_H
