#include <QCoreApplication>
#include <QVariantMap>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

void ReadWriteJsonFile_1()
{
    QVariantMap personWrite;
    personWrite["name"] = "张三";
    personWrite["sex"] = "man";
    personWrite["age"] = 33;
    QVariantMap carWrite;
    carWrite["carName"] = "奥迪";
    carWrite["price"] = "15万";
    personWrite["car"] = carWrite;
    QJsonDocument jsonDocWrite = QJsonDocument::fromVariant(personWrite);
    QByteArray byteArrWrite = jsonDocWrite.toJson(QJsonDocument::Indented);    //Indented带有缩进格式的json
    QFile fileWrite("person.json");
    fileWrite.open(QFile::WriteOnly);
    fileWrite.write(byteArrWrite);
    fileWrite.close();

    QFile fileRead("person.json");
    fileRead.open(QFile::ReadOnly);
    QByteArray byteArrRead = fileRead.readAll();
    fileRead.close();
    QJsonParseError jsonErr;
    QJsonDocument jsonDocRead = QJsonDocument::fromJson(byteArrRead, &jsonErr);
    if (jsonErr.error != QJsonParseError::NoError)
    {
        qDebug() << "QJsonDocument::fromJson:" << jsonErr.error;
        return;
    }
    QVariantMap personRead = jsonDocRead.toVariant().toMap();
    qDebug() << personRead["name"].toString().toUtf8().constData();
    qDebug() << personRead["sex"].toString().toUtf8().constData();
    qDebug() << personRead["age"].toUInt();
    QVariantMap carRead = personRead["car"].toMap();
    qDebug() << carRead["carName"].toString().toUtf8().constData();
    qDebug() << carRead["price"].toString().toUtf8().constData();
}

void WriteQJsonObjectToJsonFile_1()
{
    QJsonObject obj;    //对象类型就和QVariantMap类似
    QJsonValue v;   //isBool, isDouble, QJsonValue有各种数据类型可以转换
    v = "张三";
    obj.insert("name", v);
    obj["age"] = 50;
//    QJsonDocument jsonDocWrite = QJsonDocument::fromVariant(obj);   //第一种载入数据方法
    QJsonDocument jsonDocWrite; //QJsonDocument只有isArray,isObject两种类型
    jsonDocWrite.setObject(obj);  //第二种载入数据方法
    QByteArray byteArrWrite = jsonDocWrite.toJson(QJsonDocument::Indented);
    QFile fileWrite("person_1.json");
    fileWrite.open(QFile::WriteOnly);
    fileWrite.write(byteArrWrite);
    fileWrite.close();
}

void WriteQJsonArrayToJsonFile_1()
{
//    QStringList strList;  //第一种载入数据
//    strList.append("王五");
//    strList.append("赵六");

    QJsonArray arr; //数组类型和列表类似，这是第二种载入数据
    QJsonValue v1;
    v1 = "李四";
    arr.append(v1);
    QJsonValue v2;
    v2 = "王五";
    arr.push_back(v2);

//    QJsonDocument jsonDoc = QJsonDocument::fromVariant(strList);    //第一种载入数据方法
    QJsonDocument jsonDoc;
    jsonDoc.setArray(arr);  //第二种载入数据方法
//    QByteArray ba = jsonDoc.toBinaryData();  //这是二进制形式的json，写入文件显示乱码
    QByteArray ba = jsonDoc.toJson(QJsonDocument::Indented);
    QFile fileWrite("person_2.json");
    fileWrite.open(QFile::WriteOnly);
    fileWrite.write(ba);
    fileWrite.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReadWriteJsonFile_1();

    WriteQJsonObjectToJsonFile_1();

    WriteQJsonArrayToJsonFile_1();

    return a.exec();
}
