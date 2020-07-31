#include "qqtttreenode.h"
#include <QVariant>
#include "qqtttreecolumnsdata.h"
#include <QFont>
#include <QColor>
#include <QIcon>

QQttTreeNode* QQttTreeNode::createQttTreeNode(QQttTreeNode *aParentTreeNode, QString &aName, QString &aAreaSize, QString &aPopulation)
{
    QQttTreeNode *treeNode = new QQttTreeNode(aParentTreeNode);
    QQttTreeColumnsData *treeColumnsData = new QQttTreeColumnsData(treeNode);
    treeColumnsData->setName(aName);
    treeColumnsData->setAreaSize(aAreaSize);
    treeColumnsData->setPopulation(aPopulation);
    treeNode->setTreeColumnsData(treeColumnsData);
    return treeNode;
}

QQttTreeNode::QQttTreeNode(QQttTreeNode *aParentTreeNode)
    : QObject(aParentTreeNode)
    , mChecked(false)
{
    mParentTreeNode = aParentTreeNode;
}

QQttTreeNode::~QQttTreeNode()
{
}

QQttTreeNode* QQttTreeNode::parentTreeNode() const
{
    return mParentTreeNode;
}

void QQttTreeNode::appendChild(QQttTreeNode *aTreeNode)
{
    aTreeNode->setRow(mChildTreeNodeList.count());
    mChildTreeNodeList.append(aTreeNode);
}

void QQttTreeNode::removeChild(quint16 aIndex)
{
    mChildTreeNodeList.removeAt(aIndex);
}

void QQttTreeNode::setTreeColumnsData(QQttTreeColumnsData *aTreeColumnsData)
{
    mTreeColumnsData = aTreeColumnsData;
}

quint16 QQttTreeNode::childTreeNodeCount() const
{
    return mChildTreeNodeList.count();
}

QQttTreeNode* QQttTreeNode::childTreeNode(quint16 aRowIndex) const
{
    return mChildTreeNodeList.value(aRowIndex);
}

void QQttTreeNode::setRow(const quint16 aRow)
{
    mRow = aRow;
}

quint16 QQttTreeNode::row() const
{
    return mRow;
}

QVariant QQttTreeNode::text(quint16 aColIndex) const
{
    switch (aColIndex)
    {
        case QQttTreeColumnsData::cdtName:
            return mTreeColumnsData->name();
        case QQttTreeColumnsData::cdtAreaSize:
            return mTreeColumnsData->areaSize();
        case QQttTreeColumnsData::cdtPopulation:
            return mTreeColumnsData->population();
        default:
            return QVariant();
    }
}

QVariant QQttTreeNode::font(quint16 aColIndex) const
{
    if (aColIndex == QQttTreeColumnsData::cdtName)  //把column名称类型数据都加粗
    {
        QFont f;
        f.setBold(true);    //设置粗体
        return f;
    }
    return QVariant();
}

QVariant QQttTreeNode::color(quint16 aColIndex) const
{
    if (aColIndex == QQttTreeColumnsData::cdtAreaSize)  //把面积类型数据都变红色
    {
        return QColor(Qt::red);
    }
    return QVariant();
}

QVariant QQttTreeNode::backgroundColor(quint16 aColIndex) const
{
    if ((row() % 2 == 0) and (aColIndex == QQttTreeColumnsData::cdtAreaSize))   //偶数行(0,2,4,...)并且在面积那一列
    {
        return QColor(Qt::green);
    }
    return QVariant();
}

QVariant QQttTreeNode::textAlign(quint16 aColIndex) const
{
    if (aColIndex == QQttTreeColumnsData::cdtAreaSize)
    {
        return QVariant(Qt::AlignCenter);   //中间对齐由垂直中间对齐和水平中间对齐组合
    }
    else if (aColIndex == QQttTreeColumnsData::cdtPopulation)
    {
        return QVariant(Qt::AlignVCenter|Qt::AlignRight);   //垂直中间对齐和右边对齐
    }
    return QVariant();
}

QVariant QQttTreeNode::icon(quint16 aColIndex) const
{
    if (aColIndex == QQttTreeColumnsData::cdtName)
    {
        return QIcon("D:/qtt/QtWorkSpace/QTreeView_QAbstractItemModel_1/QTreeView_QAbstractItemModel_1/cdtName.png");
    }
    return QVariant();
}

bool QQttTreeNode::isChecked() const
{
    return mChecked;
}

void QQttTreeNode::setChecked(bool aChecked)
{
    mChecked = aChecked;
}

bool QQttTreeNode::checkable(quint8 aColIndex) const
{
    if (aColIndex == QQttTreeColumnsData::cdtName)
    {
        return true;
    }
    return false;
}
