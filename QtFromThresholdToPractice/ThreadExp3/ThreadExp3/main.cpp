#include "widget.h"
#include <QApplication>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "main thread:" << QThread::currentThreadId();
    Widget w;
    w.show();
    return a.exec();
}
