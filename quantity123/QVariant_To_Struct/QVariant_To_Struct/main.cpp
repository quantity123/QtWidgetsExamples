#include <QCoreApplication>
#include <QDebug>

struct Student
{
    QString name;
    quint8 age;
    operator QVariant() const   //把QVariant参数写到这里重载，调用时候就可以省略下面的代码
    {
        return QVariant::fromValue(*this);
    }
    Student()
    {
    }
    Student(const QVariant& variant)
    {
        *this = variant.value<Student>();
    }
};
Q_DECLARE_METATYPE(Student)

void setVariant(const QVariant& aValue)
{
    qDebug() << aValue;
}

void setStudent(const Student& st)
{
    qDebug() << "setStudent" << st.name << st.age;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringStrem;
    Student stu1;
    stu1.name = "张三";
    stu1.age = 30;

    //自定义类型转QVariant
    QVariant variant;
//    variant.setValue(stu1);   //自定义类型转QVariant方法1
    variant = QVariant::fromValue(stu1);    //自定义类型转QVariant方法2sss
//    setVariant(variant);
//    setVariant(stu1);   //自定义类型转QVariant方法3,Student类里面重载了QVariant类型操作

    //QVariant转自定义类型
//    Student stu2;
//    stu2 = variant.value<Student>();    //QVariant类型转换自定义类型1
//    setStudent(stu2);

    setStudent(variant);     //QVariant类型转换自定义类型2，Student类里面重载了Student类型操作







    return a.exec();
}
