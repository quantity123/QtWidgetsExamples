#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("file.dat");

    file.open(QIODevice::ReadWrite);
    QDataStream out(&file);
    out << QString("the answer is");
    out << (quint8)33;
    //立即从流当中读出数据
    QString ss;
    //要把游标设置为0才能继续读取，否则游标在末尾，什么也读取不到
    out.device()->seek(0);
    out >> ss;
    qDebug() << ss;
    file.close();

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QString s;
    quint8 n;
    in >> s >> n;
    qDebug() << s.toUtf8().constData() << n;    //toUtf8.constData()去掉双引号
    file.close();

    return a.exec();
}
