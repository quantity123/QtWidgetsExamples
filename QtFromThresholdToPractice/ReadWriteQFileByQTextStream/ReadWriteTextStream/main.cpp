#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("file.txt");
    auto openRet = file.open(QFile::WriteOnly | QFile::Truncate);
    if (openRet)
    {
        QTextStream out(&file);
        out.setCodec("UTF-8");  //设置编码格式
        out << "The answer is " << 45;
        file.close();
    }

    auto openRet1 = file.open(QFile::ReadOnly);
    if (openRet1)
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QString s = in.readAll();
        qDebug() << s.toUtf8().constData();
        file.close();
    }

    return a.exec();
}
