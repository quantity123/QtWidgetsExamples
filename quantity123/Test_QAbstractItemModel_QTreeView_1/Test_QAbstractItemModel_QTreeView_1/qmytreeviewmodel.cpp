#include "qmytreeviewmodel.h"
#include <QDateTime>
#include <QColor>
#include <QSize>
#include <QFont>
#include <QBrush>

QMyTreeViewModel::QMyTreeViewModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    clear();
}

void QMyTreeViewModel::setFlashData(QList<QFlashIndexData> &flash_data)
{
    mFlashIndex = flash_data;
//    resetInternalData();
    beginResetModel();
    endResetModel();
    emit stateChanged(Qt::Unchecked);
}

void QMyTreeViewModel::clear()
{
    mFlashIndex.clear();
    beginResetModel();
    endResetModel();
    emit stateChanged(Qt::Unchecked);
}

void QMyTreeViewModel::getSelectedFlashData(QMap<quint32, quint16> &selected_list)
{
    selected_list.clear();
    for (int i=0; i<rowCount(); ++i)
    {
        if (mFlashIndex.at(i).is_be_checked)
        {
            selected_list.insert(mFlashIndex.at(i).unix_time, mFlashIndex.at(i).addr);
        }
    }
}

QVariant QMyTreeViewModel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        switch (section)
        {
        case CHECK_BOX_COLUMN:
            return QString("全选");
            break;
        case UNIX_TIME_COLUMN:
            return QString("时间");
            break;
        case FLASH_ADDR_COLUMN:
            return QString("地址");
            break;
        default:
            return "";
            break;
        }
        break;
    case Qt::FontRole:
        return QFont("SimSun", 12);
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;
    case Qt::TextColorRole:
        return QColor(Qt::black);
        break;
    case Qt::SizeHintRole:
        return QSize(100, 40);
        break;
    case Qt::BackgroundRole:
        return QBrush(Qt::black);
        break;
    default:
        break;
    }
    return QVariant();
}

//bool QMyTreeViewModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}

QModelIndex QMyTreeViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || column < 0 || column >= columnCount(parent))
        return QModelIndex();
    return createIndex(row, column);
}

QModelIndex QMyTreeViewModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int QMyTreeViewModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    Q_UNUSED(parent);
    return mFlashIndex.count();
}

int QMyTreeViewModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    Q_UNUSED(parent);
    return 3;
}

//获取role角色的数据
QVariant QMyTreeViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    QFlashIndexData indexData = mFlashIndex[row];
    int column = index.column();
    switch (role)
    {
    case Qt::DisplayRole:
        if (column == UNIX_TIME_COLUMN)
            return QDateTime::fromTime_t(indexData.unix_time).toString("yyyy-MM-dd hh:mm:ss");
        else if (column == FLASH_ADDR_COLUMN)
            return indexData.addr;
        else
            return "";
        break;
    case Qt::CheckStateRole:
        if (column == CHECK_BOX_COLUMN)
            return indexData.is_be_checked ? Qt::Checked : Qt::Unchecked;
        break;
    case Qt::TextAlignmentRole:
        if (column == CHECK_BOX_COLUMN)
            return QVariant(Qt::AlignLeft|Qt::AlignVCenter);
        else
            return Qt::AlignCenter;
        break;
    case Qt::TextColorRole:
        return QColor(Qt::black);
        break;
    case Qt::SizeHintRole:
        return QSize(100, 30);
        break;
    case Qt::FontRole:
        return QFont("SimSun", 11);
        break;
    default:
        break;
    }
    return QVariant();
}

//设置role角色的数据，可编辑，只提供可选或不可选的编辑，不提供对数据源的编辑
bool QMyTreeViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }

    if (index.isValid())
    {
        int column = index.column();
        auto indexData = mFlashIndex.at(index.row());
        switch (role)
        {
        case Qt::UserRole:  //根据表头的复选框选择
            break;
        case Qt::UserRole+1:    //根据鼠标点击
            if (column == CHECK_BOX_COLUMN)
            {
                indexData.is_be_checked = static_cast<Qt::CheckState>(value.toUInt()) == Qt::Checked;
                mFlashIndex.replace(index.row(), indexData);
                emit dataChanged(index, index);
                if (role == Qt::UserRole+1) //点击鼠标，更新表头复选框状态
                    onStateChanged();
                return true;
            }
            break;
        default:
            break;
        }
    }
    return false;
}

Qt::ItemFlags QMyTreeViewModel::flags(const QModelIndex &index) const
{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable; // FIXME: Implement me!

    if (!index.isValid())
        return QAbstractItemModel::flags(index);
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
    if (index.column() == CHECK_BOX_COLUMN)
        flags |= Qt::ItemIsUserCheckable;
    return flags;
}

void QMyTreeViewModel::slot_stateChanged(Qt::CheckState state)
{
    for (int i=0; i<rowCount(); ++i)
    {
        setData(index(i, CHECK_BOX_COLUMN), state, Qt::UserRole);
    }
}

void QMyTreeViewModel::onStateChanged()
{
    int select_total = 0;
    for (int i=0; i<rowCount(); ++i)
    {
        if (mFlashIndex.at(i).is_be_checked)
            ++select_total;
    }
    if (select_total == 0)
    {
        emit stateChanged(Qt::Unchecked);
    }
    else if (select_total < rowCount())
    {
        emit stateChanged(Qt::PartiallyChecked);
    }
    else
    {
        emit stateChanged(Qt::Checked);
    }
}
