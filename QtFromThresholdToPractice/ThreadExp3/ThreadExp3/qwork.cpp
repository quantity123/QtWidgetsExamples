#include "qwork.h"
#include <QDebug>
#include <QThread>

QWork::QWork(QObject *parent) : QObject(parent)
{

}

void QWork::slotDrawImage()
{
    qDebug() << "qwork thread:" << QThread::currentThreadId();

    QImage image(600, 600, QImage::Format_ARGB32);
    QPainter painter(&image);
    QPoint ptArr[] =
    {
        QPoint(qrand()%590, qrand()%590),
        QPoint(qrand()%590, qrand()%590),
        QPoint(qrand()%590, qrand()%590),
        QPoint(qrand()%590, qrand()%590),
        QPoint(qrand()%590, qrand()%590),
    };
    painter.drawPolygon(ptArr, 5);  //画图
    emit signalDrawImageDone(image);    //信号发送图片
}
