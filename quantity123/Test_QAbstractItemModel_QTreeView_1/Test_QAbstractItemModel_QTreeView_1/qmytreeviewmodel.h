#ifndef QMYTREEVIEWMODEL_H
#define QMYTREEVIEWMODEL_H

#include <QAbstractItemModel>

struct QFlashIndexData
{
    QFlashIndexData()
        : is_be_checked(false)
    {
    }
    bool is_be_checked;
    quint32 unix_time;
    quint16 addr;
};

class QMyTreeViewModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum
    {
        CHECK_BOX_COLUMN = 0,
        UNIX_TIME_COLUMN,
        FLASH_ADDR_COLUMN
    };

    explicit QMyTreeViewModel(QObject *parent = nullptr);
    void setFlashData(QList<QFlashIndexData> &flash_data);
    void clear();
    void getSelectedFlashData(QMap<quint32, quint16> &selected_list);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
public slots:
    void slot_stateChanged(Qt::CheckState state);
signals:
    void stateChanged(Qt::CheckState state);
private:
    void onStateChanged();
    QList<QFlashIndexData> mFlashIndex;
};

#endif // QMYTREEVIEWMODEL_H
