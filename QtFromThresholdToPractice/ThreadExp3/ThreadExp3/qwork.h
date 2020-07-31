#ifndef QWORK_H
#define QWORK_H

#include <QObject>
#include <QPainter>

class QWork : public QObject
{
    Q_OBJECT
public:
    explicit QWork(QObject *parent = nullptr);
public slots:
    void slotDrawImage();
signals:
    void signalDrawImageDone(QImage image);
};

#endif // QWORK_H
