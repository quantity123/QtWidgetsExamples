#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <QQueue>
#include <QMap>
#include <QSet>
#include <QHash>

void testQList()
{
    QList<QString> list;

    //查看列表长度，大小，数量
    qDebug() << list.length() << list.size() << list.count();

    //增加元素
    list.append("aaa");
    list.insert(1, "bbb");  //超过范围大小的插入会取最小或最大边界索引插入
    list.push_back("CCC");
    list.append("ddd");

//    list.prepend("ddd");  //预备插入元素，在其它几个增加元素的前面，越是后面预备增加的元素在列表的位置越靠前
//    list.prepend("eee");
//    list.prepend("fff");
//    list.prepend("ggg");

    //查看列表长度，大小，数量
    qDebug() << list.length() << list.size() << list.count();

    qDebug() << "显示首尾元素";
    qDebug() << list.first();   //首元素
    qDebug() << list.last();    //尾元素
    qDebug() << list.front();   //首元素
    qDebug() << list.back();    //尾元素

    //显示列表所有元素
    qDebug() << "显示列表所有元素";
    for (auto &v : list)    //容器类可以使用新c++语法
    {
        qDebug() << v;
    }

    qDebug() << "显示子列表subList所有元素";
    auto subList = list.mid(1, 2); //获取列表中的子列表，第一个参数是起始index位置，第二个参数是指定长度范围，默认-1是从指定index位置到列表末尾元素
    for (auto &v : subList) //获取子列表所有元素
    {
        qDebug() << v;
    }

    //获取元素索引
    auto index = list.indexOf("bbb");
    //获取元素
    qDebug() << "at方法获取元素";
    auto item = list.at(index);
    qDebug() << item;
    qDebug() << "at方法获取元素后修改元素";
    index = list.lastIndexOf("CCC", 1); //第二个参数是从列表结束查找的位置index，由于"CCC"在列表索引2的位置，实参是索引1结束查找，所以没有找到"CCC"元素
    qDebug() << "value方法获取元素";
    item = list.value(index);
    qDebug() << item;


//    qDebug() << list.contains("bbb"); //判断是否包含了该元素
//    qDebug() << list.startsWith("bbb");   //判断是否指定的元素开头
//    qDebug() << list.endsWith("ddd");   //判断是否指定的元素结尾
//    list.sort(Qt::CaseSensitive);   //区分大小写的排序
//    list.replaceInStrings()   //替换成字符串列表
//    list.filter() //转换成字符串列表
//    list.join("");    //转换成字符串
//    list.fromVector() //重vector列表载入数据
//    list.toVector()   //把列表数据转换给vector

    //修改元素
//    list[0] = "qqq";  //[]数组下标可以修改元素
//    list.replace(0, "qqq"); //replace可以修改元素
//    list.first() = "qqq";   //first可以修改元素
//    list.front() = "qqq";   //front可以修改元素
//    *list.begin() = "qqq";    //begin迭代器可以修改元素


    //删除元素
//    list.clear();   //删除所有元素
//    list.removeDuplicates(); //删除重复元素
//    list.removeAt(0); //根据索引删除元素
//    list.removeAll("aaa"); //删除所有指定元素值一样的元素
//    list.removeOne("aaa");  //删除一个指定元素值的元素
//    list.removeFirst();  //删除第一个元素
//    list.erase(list.begin());    //根据迭代器或者迭代器范围擦除元素
//    list.pop_front();    //弹出列表栈第一个元素
//    item = list.takeAt(0);  //获取元素对象的同时删除元素
//    item = list.takeFirst();    //获取第一个元素对象的同时删除元素

//    qDebug() << list.isEmpty();   //判断列表是否为空
//    qDebug() << list.empty();   //判断列表是否为空

    //显示列表所有元素
    qDebug() << "显示列表所有元素";
    for (auto &v : list)
    {
        qDebug() << v;
    }
}

void testQVector()
{
//    QVector<QString> vector;
    //用法和QList差不多，但是通常使用在列表末尾位置 增删改 比较快，其余位置慢
    QVector<QString> *vector = new QVector<QString>;//(3, "aaa");   //3是初始化3个元素，每个元素值是 "aaa"字符串
    for (auto &v : *vector)
    {
        qDebug() << v;
    }
    delete vector;
}

void testQQueue()
{
    //QQueue继承QList，只是多了enqueue(),dequeue(),head()方法，这个队列通常用于尾部进元素，头部出元素
    QQueue<QString> *queue = new QQueue<QString>;

    queue->append("aaa");
    queue->insert(1, "bbb");
    queue->push_back("ccc");

    queue->enqueue("ddd");  //加入一个元素到队列末尾，与append方法类似
    qDebug() << "显示队列所有元素";
    for (auto &v : *queue)
    {
        qDebug() << v;
    }
    qDebug() << "dequeue()从队列头部出一个元素，队列头部元素就删除了，也不能对其元素进行修改，与take函数类似";
    auto element = queue->dequeue();
    qDebug() << element;
    qDebug() << "显示队列所有元素";
    for (auto &v : *queue)
    {
        qDebug() << v;
    }
    qDebug() << "head()队列头部出来的元素引用，并且可以对队列头部元素进行修改";
    auto element_1 = queue->head();
    qDebug() << element_1;
    queue->head() = "qqq";  //把这个头元素"bbb"修改成"qqq"
    qDebug() << "显示队列所有元素";
    for (auto &v : *queue)
    {
        qDebug() << v;
    }

    delete queue;
}

void testQMap()
{
    //QMap主要是一个映射关系的列表，键=值 的关系
    QMap<quint8, QString> *map = new QMap<quint8, QString>;

//    map->unite()    //联合功能，与另一个QMap对象组合在一起

    //QMap增加元素功能
    map->insert(0, "aaa");
    map->insert(1, "bbb");
    map->insertMulti(2, "ccc");


    qDebug() << "查询map列表大小与数量";
    qDebug() << map->size() << map->count();

    qDebug() << "通过值bbb获取键";
    auto key = map->key("bbb");
    qDebug() << key;
//    map->keys()   //通过值获取所有相关的键
    qDebug() << "通过键1获取值";
    qDebug() << map->value(1);
//    map->values() //通过键获取所有相关的值
//    map->first()    //第一个值
//    map->firstKey() //第一个键
//    map->last()   //最后一个值
//    map->lastKey()  //最后一个键
//    map->uniqueKeys() //取出所有键给一个QList列表
//    map->contains()   //map列表里是否包含该键

    qDebug() << "显示Map列表所有元素";
    for (auto &v : *map)
    {
        qDebug() << v;
    }

//    qDebug() << "map列表元素值的修改，把值aaa为qqq，元素键不允许修改";
//    (*map)[0] = "qqq";
//    *map->find(0) = "qqq";   //通过键查找值迭代器，然后修改值
//    map->insert(0, "qqq");    //直接插入索引0位置覆盖掉原来的值，也就是aaa替换成了qqq
//    map->first() = "qqq";
//    *map->begin() = "qqq";


    qDebug() << "map列表元素的删除";
//    map->clear();   //清空所有元素
//    map->erase()    //通过迭代器来擦除一个元素
//    map->take(0);   //通过键来获取一个值并且从列表删除这个键值元素
//    qDebug() << map->remove(0);  //通过键来删除一个键值元素，返回值1删除成功,0失败

//     qDebug() << map->empty(); map->isEmpty()    //判断map列表是否为空

    qDebug() << "显示Map列表所有元素";
    for (auto &v : *map)
    {
        qDebug() << QString(v.data());
    }

    delete map;
}

void testQSet()
{
    //集合类型用途是用来做 交集，并集，对比使用的
    QSet<QString> *set = new QSet<QString>;
    //QSet增加元素，QSet元素在内部排序是无规则
    set->insert("aaa");
    set->insert("bbb");
    set->insert("ccc");
//    set->unite()  //组合其它的QSet集合

    qDebug() << "查询QSet大小与元素数量与占用空间容量";
    qDebug() << set->size() << set->count() << set->capacity();
    qDebug() << "QSet显示所有元素";
    for (auto &v : *set)
    {
        qDebug() << v;
    }
    //获取元素值
//    auto iter = set->find("aaa");   //通过值获取迭代器，但是不能修改值
//    auto iter = set->begin();    //获取第一个元素的迭代器，不能修改值
//    set->values()   //得到一个值的QList列表对象

//    set->intersect()  //返回值是一个交集
//    set->intersects() //判断是否交集

    //QSet集合的删除
//    set->clear();   //清空所有元素
//    set->erase()  //根据迭代器擦除元素
//    set->remove("aaa");
//    set->subtract() //减去其它的Qset集合

    qDebug() << "QSet显示所有元素";
    for (auto &v : *set)
    {
        qDebug() << QString(v.data());
    }

    delete set;
}

void testQHash()
{
    //QHash 与 QMap用法差不多
    QHash<quint8, QString> *hash = new QHash<quint8, QString>;
    delete hash;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    testQList();

//    testQVector();

//    testQQueue();

//    testQMap();

//    testQSet();

    testQHash();

    return a.exec();
}
