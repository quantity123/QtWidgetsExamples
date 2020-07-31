#include "qqtttreemodel.h"
#include "qqtttreecolumnsdata.h"
#include <QDebug>
#include "qqtttreenode.h"

QQttTreeModel::QQttTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , mRootTreeNode(new QQttTreeNode(nullptr))
{
    mTreeColumnHeaderList.append("名称");
    mTreeColumnHeaderList.append("面积");
    mTreeColumnHeaderList.append("人口");
    createTree();
}

QQttTreeModel::~QQttTreeModel()
{
    mTreeColumnHeaderList.clear();
    delete mRootTreeNode;   //给所有的子节点都设置了父对象，所以在这里把根root节点释放，root的子节点全部释放
}

QQttTreeNode* QQttTreeModel::NodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
    {
        QQttTreeNode *treeNode = static_cast<QQttTreeNode*>(index.internalPointer());
        return treeNode;
    }
    return mRootTreeNode;
}

QVariant QQttTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //columnCount执行完毕后执行这里
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return mTreeColumnHeaderList.at(section);
        }
    }
    return QVariant();
}

QModelIndex QQttTreeModel::index(int row, int column, const QModelIndex &parent) const  //parent是父索引
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QQttTreeNode *parentTreeNode = NodeFromIndex(parent);
    QQttTreeNode *treeNode = parentTreeNode->childTreeNode(row);
    if (treeNode != nullptr)
        return createIndex(row, column, treeNode);
    else
        return QModelIndex();
}

QModelIndex QQttTreeModel::parent(const QModelIndex &index) const
{
    QQttTreeNode *treeNode = NodeFromIndex(index);
    QQttTreeNode *parentNode = treeNode->parentTreeNode();

    if (parentNode == mRootTreeNode)
        return QModelIndex();
    int row = parentNode->row();
    return createIndex(row, 0, parentNode);
}

int QQttTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;
    QQttTreeNode *treeNode = NodeFromIndex(parent);
    return treeNode->childTreeNodeCount();
}

int QQttTreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    //首先进入这里设置列数量
    return mTreeColumnHeaderList.size();
}

QVariant QQttTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QQttTreeNode *treeNode = NodeFromIndex(index);
    switch (role)
    {
    case Qt::DisplayRole:
        return treeNode->text(index.column());
    case Qt::FontRole:
        return treeNode->font(index.column());
    case Qt::TextColorRole:
        return treeNode->color(index.column());
    case Qt::BackgroundRole:
        return treeNode->backgroundColor(index.column());
    case Qt::TextAlignmentRole:
        return treeNode->textAlign(index.column());
    case Qt::DecorationRole:
        return treeNode->icon(index.column());
    case Qt::CheckStateRole:
        if (treeNode->checkable(index.column()))
        {
            return treeNode->isChecked() ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

Qt::ItemFlags QQttTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.isValid())
    {
        QQttTreeNode *treeNode = NodeFromIndex(index);
        if (treeNode->checkable(index.column()))
        {
            flags |= Qt::ItemIsUserCheckable;   //增加用户操作checkbox的标志，也就能操作的权限
        }
    }
    return flags;
}

bool QQttTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid())
    {
        if (role == Qt::CheckStateRole)
        {
            QQttTreeNode *treeNode = NodeFromIndex(index);
            if (treeNode->checkable(index.column()))
            {
                bool checked = (value.toUInt() == Qt::Checked);
                treeNode->setChecked(checked);
                emit dataChanged(index, index);
                return true;
            }
        }
    }
    return false;
}

void QQttTreeModel::createTree()
{
    QString name;
    QString areaSize;
    QString population;
    name = "中国";
    areaSize = "960万平方公里";
    population = "14亿";
    QQttTreeNode *firstChildTreeNode = QQttTreeNode::createQttTreeNode(mRootTreeNode, name, areaSize, population);
    mRootTreeNode->appendChild(firstChildTreeNode);
    for (quint8 i=0; i<3; ++i)
    {
        switch (i)
        {
        case 0:
            name = "湖北";
            areaSize = "18.59万平方公里";
            population = "5927万";
            break;
        case 1:
            name = "浙江";
            areaSize = "18.59万平方公里";
            population = "5927万";
            break;
        case 2:
            name = "江苏";
            areaSize = "18.59万平方公里";
            population = "5927万";
            break;
        default:
            break;
        }
        QQttTreeNode *secondChildTreeNode = QQttTreeNode::createQttTreeNode(firstChildTreeNode, name, areaSize, population);
        firstChildTreeNode->appendChild(secondChildTreeNode);
    }
}
