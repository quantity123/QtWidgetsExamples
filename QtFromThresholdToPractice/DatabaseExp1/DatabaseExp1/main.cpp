#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QStringList>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlField>
#include <QTableView>
#include <QAbstractItemView>

bool connectToDatabase(QSqlDatabase &db, bool aIsMySql, QString aConnectionName, QString aDbName, QString aHost="", QString aUserName="", QString aPassword="")
{
    if (aIsMySql)
    {
        db = QSqlDatabase::addDatabase("QMYSQL", aConnectionName);
        db.setHostName(aHost);
        //db.setPort(3306);
        db.setUserName(aUserName);
        db.setPassword(aPassword);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", aConnectionName); //本地数据库不存在就创建一个新的
    }
    db.setDatabaseName(aDbName);
    auto openRet = db.open();
    if (openRet)
    {
        return true;
    }
    return false;
}

void useQSqlQuery(QSqlDatabase &db)
{
    QSqlQuery query(db);
    QString sql;
    bool queryRet;

    //创建表
//    QStringList sl;
//    sl.append("CREATE TABLE student");
//    sl.append("(");
//    sl.append("id INTEGER PRIMARY KEY AUTOINCREMENT,");
//    sl.append("name VARCHAR(255),");
//    sl.append("age INTEGER");
//    sl.append(")");
//    sql = sl.join("");
//    queryRet = query.exec(sql);
//    if (queryRet)
//    {
//        qDebug() << "INSERT INTO student success!";
//    }
//    else
//    {
//        qDebug() << query.lastError().text();
//        return 2;
//    }

    //批量插入数据
//    sql = "INSERT INTO student(name, age)VALUES(?, ?)";
//    sql = "INSERT INTO student(name, age)VALUES(:name, :age)";    //以后测试下字段名字是否能用 : 形式绑定，测试下 select,update,delete 能否用 : 绑定
//    query.prepare(sql); //这种方式载入sql后面要用execBatch执行
//    QVariantList names;
//    names << "Tom" << "Jack" << "Jane" << "Jerry";
//    query.addBindValue(names);//可以绑定一个或列表
//    query.addBindValue(":name", names);
//    QVariantList ages;
//    ages << 20 << 23 << 22 << 25;
//    query.addBindValue(ages);
//    query.addBindValue(":age", ages);
//    queryRet = query.execBatch(); //批量记录执行
//    queryRet = query.exec();  //单个记录执行
//    if (queryRet)
//    {
//        qDebug() << "INSERT INTO student success!";
//    }
//    else
//    {
//        qDebug() << query.lastError().text();
//        return 3;
//    }

    //查询表
    sql = "SELECT id, name, age FROM student";
    queryRet = query.exec(sql);
    if (queryRet)
    {
        qDebug() << "SELECT student success!";
        while (query.next())
        {
            QSqlRecord record = query.record();
            auto id = record.value("id").toUInt();
//            QString name = query.value(0).toString();
            auto name = record.value("name").toString();
//            qlonglong age = query.value(1).toUInt();
            auto age = record.value("age").toUInt();
            qDebug() << query.at() << id <<  name << ":" << age;
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void useQSqlTableModelSlect(QSqlDatabase &db)
{
    QSqlTableModel tableModel(nullptr, db);
    tableModel.setTable("student");
    tableModel.setFilter("age >= 20 and age <= 25");
    if (tableModel.select())
    {
        for(quint8 i=0; i<tableModel.rowCount(); ++i)
        {
            QSqlRecord record = tableModel.record(i);   //得到一行数据记录
            quint8 id = record.value("id").toUInt();
            QString name = record.value("name").toString();
            quint8 age = record.value("age").toUInt();
            qDebug() << id << name << ":" << age;
        }
    }
}

void useQSqlTableModelInsert(QSqlDatabase &db)
{
    QSqlTableModel tableModel(nullptr, db);
    tableModel.setTable("student");
    //quint8 row = 0;

    //插入数据方式1
    tableModel.insertRow(0);  //新增record记录插入第row行
    tableModel.setData(tableModel.index(0, 1), "ChenFeng");   //第row行第1列设置数据
    tableModel.setData(tableModel.index(0, 2), 24);
    tableModel.submit();

    //插入数据方式2
    QSqlRecord record;
    QSqlField nameField("name");
    QSqlField ageField("age");
    record.append(nameField);
    record.append(ageField);
    record.setValue("name", "liuhouzheng");
    record.setValue("age", 25);
//    ++row;
    tableModel.insertRecord(0, record);
    //提交插入的数据记录
    tableModel.submit();

    //tableModel.submitAll()    //上面两个不能一次性提交
}

void useQSqlTableModelModify(QSqlDatabase &db)
{
    QSqlTableModel tableModel(nullptr, db);
    tableModel.setTable("student");
    tableModel.setFilter("age = 24");
    if (tableModel.select())
    {
        for (quint8 i=0; i<tableModel.rowCount(); ++i)
        {
            QSqlRecord record = tableModel.record(0);
            record.setValue("age", 21);
            tableModel.setRecord(0, record);
            //tableModel.submit();  //提交单行记录修改
        }
        tableModel.submitAll(); //提交所有行记录修改
    }
}

void useQSqlTableModelDelete(QSqlDatabase &db)
{
    QSqlTableModel tableModel(nullptr, db);
    tableModel.setTable("student");
    tableModel.setFilter("age = 20");
    if (tableModel.select())
    {
        for (quint8 i=0; i<tableModel.rowCount(); ++i)
        {
            //quint8 count = tableModel.rowCount();
            tableModel.removeRow(i);    //测试removeRows不能批量删除可以单个删除与removeRow函数功能一样了
        }
        tableModel.submitAll();
    }
}

void useQSqlTableModelShowTableView(QSqlDatabase &db)
{
    QSqlTableModel tableModel(nullptr, db);
    tableModel.setTable("student");
    tableModel.setSort(1, Qt::AscendingOrder);  //升序排列
    tableModel.setHeaderData(1, Qt::Horizontal, "name");
    tableModel.setHeaderData(2, Qt::Horizontal, "age");
    tableModel.select();
    //重新查询
//    tableModel.setTable("student");
//    tableModel.select();

    QTableView tableView;
    tableView.setModel(&tableModel);
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);    //表格选择数据的模式：单一行选择
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);  //选择数据的行为：选择行
    //tableView.setColumnHidden(0, true);   //第0列隐藏
    tableView.resizeColumnsToContents();    //每列宽度自动适配其内容
    tableView.setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置禁用编辑功能
    tableView.show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //查看哪些数据库驱动可以用
//    qDebug() << QSqlDatabase::drivers();
//    return 0;

    QSqlDatabase db;
    auto connectRet = connectToDatabase(db, false, "ConnectToSqlite", "anytalk_database.db");
//    auto connectRet = connectToDatabase(db, true, "anytalk_mysql", "anytalk_database", "192.168.31.11", "root", "123456");
    if (connectRet)
    {
        qDebug() << "connectToDatabase true!";
    }
    else
    {
        qDebug() << db.lastError().text();
        return 1;
    }


    useQSqlQuery(db);

//    useQSqlTableModelInsert(db);

//    useQSqlTableModelModify(db);

//    useQSqlTableModelDelete(db);

    useQSqlTableModelSlect(db);

    useQSqlTableModelShowTableView(db);

    return a.exec();
}
