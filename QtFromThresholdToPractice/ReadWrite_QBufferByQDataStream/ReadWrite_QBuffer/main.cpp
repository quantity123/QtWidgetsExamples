#include <QCoreApplication>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //写数据
    QBuffer buf;

    buf.open(QBuffer::WriteOnly);
    QDataStream out(&buf);
    out << static_cast<QString>("Hello, QT!");
    buf.close();

    buf.open(QBuffer::ReadOnly);
    QDataStream in(&buf);
    QString s;
    in >> s;
    buf.close();
    qDebug() << s.toUtf8().constData();

    return a.exec();
}
