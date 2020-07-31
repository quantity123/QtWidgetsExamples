#ifndef QQTTTREEITEM_H
#define QQTTTREEITEM_H

#include <QObject>
#include <QList>
#include <QVariant>

class QQttTreeColumnsData;

class QQttTreeNode : public QObject
{
    Q_OBJECT
public:
    static QQttTreeNode* createQttTreeNode(QQttTreeNode *aParentTreeNode, QString &aName, QString &aAreaSize, QString &aPopulation);
    explicit QQttTreeNode(QQttTreeNode *aParentTreeNode);
    ~QQttTreeNode();
    QQttTreeNode* parentTreeNode() const;
    void appendChild(QQttTreeNode *aTreeNode);
    void removeChild(quint16 aIndex);
    void setTreeColumnsData(QQttTreeColumnsData *aTreeColumnsData);
    quint16 childTreeNodeCount() const;
    QQttTreeNode* childTreeNode(quint16 aRowIndex) const;
    void setRow(const quint16 aRow);
    quint16 row() const;
    QVariant text(quint16 aColIndex) const;
    QVariant font(quint16 aColIndex) const;
    QVariant color(quint16 aColIndex) const;
    QVariant backgroundColor(quint16 aColIndex) const;
    QVariant textAlign(quint16 aColIndex) const;
    QVariant icon(quint16 aColIndex) const;
    bool isChecked() const;
    void setChecked(bool aChecked);
    bool checkable(quint8 aColIndex) const;

signals:

private:
    bool mChecked;
    quint16 mRow;   //当前节点在第几行
    QQttTreeColumnsData *mTreeColumnsData;
    QList<QQttTreeNode*> mChildTreeNodeList;
    QQttTreeNode *mParentTreeNode;
};

#endif // QQTTTREEITEM_H
