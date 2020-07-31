#ifndef QQTTTREEMODEL_H
#define QQTTTREEMODEL_H

#include <QAbstractItemModel>

class QQttTreeNode;

class QQttTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit QQttTreeModel(QObject *parent = nullptr);
    ~QQttTreeModel();
    QQttTreeNode* NodeFromIndex(const QModelIndex &index) const;
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;   //增加了checkbox操作标志权限
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;    //增加设置checkbox的操作
private:
    void createTree();
    QStringList mTreeColumnHeaderList;
    QQttTreeNode *mRootTreeNode;
};

#endif // QQTTTREEMODEL_H
