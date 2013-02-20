#ifndef SORTER_H
#define SORTER_H

#include <QObject>
#include <QThread>
#include <QVector>

#include "sorterworker.h"

class Sorter : public QObject
{
    Q_OBJECT

    public:
        Sorter();
        ~Sorter();

        // Ordenar asíncronamente un vector en el hilo de trabajo
        void sortAsync(const QVector<int>& list);

    signals:
        // Señal para comunicarnos con el hilo de trabajo
        void sortingRequested(const QVector<int> &list);

    private slots:
        // Slot para saber cuando el vector ha sido ordenado
        void vectorSorted(const QVector<int> &list);

    private:
        // Clase del hilo de trabajo
        QThread workingThread_;
        // Clase que hace el ordenamiento
        SorterWorker sorterWorker_;
};

#endif // SORTER_H
