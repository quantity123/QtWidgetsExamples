#include "qcitymodel.h"

QCityModel::QCityModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

//初始化数据源
void QCityModel::setCities(const QStringList &aCityNames)
{
    mCities = aCityNames;
    //重新设置下QVector distances的矩阵大小，中间对角线为0不用存
    mDistances.resize(mCities.count() * (mCities.count()-1) / 2);
    //填充所有距离值为0
    mDistances.fill(0);
    //刷新所有关联的视图数据
    this->resetInternalData();
}

//返回表头名称(行号或列号，水平或垂直，角色)
QVariant QCityModel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    //返回在cities字符串列表中给定便宜量的城市名称
    if (role != Qt::DisplayRole)
        return QVariant();
    return mCities[section]; //section将取mCities列表0至count-1索引
}

int QCityModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mCities.count();
}

int QCityModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mCities.count();
}

//赋值模型每个项的数据
QVariant QCityModel::data(const QModelIndex &index, int role) const
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
            if (index.row() == index.column())
                return 0;
            int offset = offsetOf(index.row(), index.column());
            return mDistances[offset];
            break;
        }
        default:
        {
            break;
        }
    }

    return QVariant();
}

//编辑设置一个项
bool QCityModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column() && role == Qt::EditRole)
    {
        int offset = offsetOf(index.row(), index.column());
        mDistances[offset] = value.toInt();
        //交换对应项的模型索引
        QModelIndex transposedIndex = createIndex(index.column(), index.row());
        //某项发生改变，发射信号(between topleft and bottomRight inclusive)
        emit dataChanged(index, index);
//        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }
    return false;
}

//返回一个项相关的操作的标识符(例如：是否可以编辑或是否已经选中)
Qt::ItemFlags QCityModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column())
        flags |= Qt::ItemIsEditable;
    return flags;
}

//计算偏移量
int QCityModel::offsetOf(int row, int column) const
{
    if (row < column)
        qSwap(row, column);
    return (row * (row-1) / 2) + column;
}
