#ifndef QWORKER_H
#define QWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>

class QWorker : public QObject
{
    Q_OBJECT
public:
    explicit QWorker(QObject *parent = nullptr);
public slots:
    void onTimeout();
signals:

};

#endif // QWORKER_H
