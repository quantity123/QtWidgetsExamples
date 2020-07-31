#include "qmyitemmodel.h"

QMyItemModel::QMyItemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant QMyItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return section;
    }
    return QVariant();
}

QModelIndex QMyItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column, nullptr);
}

QModelIndex QMyItemModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int QMyItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return 3;
}

int QMyItemModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return 3;
}

QVariant QMyItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole)
    {
        return row + col;
    }

    return QVariant();
}
