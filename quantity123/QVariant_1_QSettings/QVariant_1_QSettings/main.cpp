#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

void readWriteQStringList(QSettings *aSetting)
{
    //写入
    QStringList listWrite;
    listWrite.append("张三");
    listWrite.append("李四");
    listWrite.append("王五");
    aSetting->setValue("Attribute/NameList", listWrite);

    //读取
    QStringList listRead;
    listRead = aSetting->value("Attribute/NameList").toStringList();    //QVariant能通过toXXXX转换到各种类型
    qDebug() << listRead;
}

void readWriteQMap(QSettings *aSetting)
{
    //写入
    QMap<QString, QVariant> personWrite;
    personWrite.insert("name", "张三");
    personWrite["age"] = 25;
    aSetting->setValue("Attribute/Person", personWrite);

    //读取
    QMap<QString, QVariant> personRead;
    personRead = aSetting->value("Attribute/Person").toMap();
    qDebug() << personRead;
}

void readWriteQMapInQMap(QSettings *aSetting)
{
    //写入
    QMap<QString, QVariant> car;
    car["brand"] = "Audi";
    car.insertMulti("price", "20万");

    QMap<QString, QVariant> personCarWrite;
    personCarWrite["name"] = "李四";
    personCarWrite["sex"] = "男";
    personCarWrite["car"] = car;

    aSetting->setValue("Attribute/PersonCar", personCarWrite);

    //读取
    QMap<QString, QVariant> personCarRead;
    personCarRead = aSetting->value("Attribute/PersonCar").toMap();
    qDebug() << personCarRead;
}

void readWriteQMapInQList(QSettings *aSetting)
{
    //写入
    QMap<QString, QVariant> person1;
    person1["name"] = "张三";
    person1["age"] = 30;
    person1["sex"] = "man";
    QMap<QString, QVariant> person2;
    person2["name"] = "李四";
    person2["age"] = "40";
    person2["sex"] = "woman";
    QList<QVariant> listWrite;
    listWrite.append(person1);
    listWrite.append(person2);
    aSetting->setValue("Attribute/PersonList", listWrite);
    //读取
    QList<QVariant> listRead;
    listRead = aSetting->value("Attribute/PersonList").toList();
    qDebug() << listRead;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings("setting.ini", QSettings::IniFormat);

    readWriteQStringList(&settings);

    qDebug() << "---------------------------------------------------------------------";

    readWriteQMap(&settings);

    qDebug() << "---------------------------------------------------------------------";

    readWriteQMapInQMap(&settings);

    qDebug() << "---------------------------------------------------------------------";

    readWriteQMapInQList(&settings);

    qDebug() << "---------------------------------------------------------------------";

    return a.exec();
}
