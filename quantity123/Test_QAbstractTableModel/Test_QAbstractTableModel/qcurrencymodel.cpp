#include "qcurrencymodel.h"

QCurrencyModel::QCurrencyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void QCurrencyModel::setCurrencyMap(const QMap<QString, double> &aCurrencyMap)
{
    mCurrencyMap = aCurrencyMap;
    this->resetInternalData();    //重置模型到原始状态，告诉所有视图数据都无效并强制刷新数据
}

//返回表头名称(行号或列号，水平或垂直，角色)
QVariant QCurrencyModel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    return at(section);
}

int QCurrencyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mCurrencyMap.count();
}

int QCurrencyModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mCurrencyMap.count();
}

//返回一个项的任意角色值，这个项被指定为QModelIndex
QVariant QCurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
        case Qt::TextAlignmentRole:
        {
            return int(Qt::AlignRight | Qt::AlignVCenter);
            break;
        }
        case Qt::DisplayRole:
        {
            QString rowKey = at(index.row());
            auto rowValue = mCurrencyMap.value(rowKey);
            if (rowValue == 0.0)
                return "####";
            QString columnKey = at(index.column());
            auto amount = mCurrencyMap.value(columnKey) / rowValue;
            return QString("%1").arg(amount, 0, 'f', 5);    //0表示不够的用0补全，'f'表示浮点数，4表示浮点数后面几位小数，超过的四去五入
            break;
        }
        default:
        {
            break;
        }
    }

    return QVariant();
}

QString QCurrencyModel::at(int offset) const
{
    return (mCurrencyMap.constBegin()+offset).key();    //迭代器+偏移量获取值
}
