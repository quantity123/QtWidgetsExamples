#ifndef QCITYMODEL_H
#define QCITYMODEL_H

#include <QAbstractTableModel>

class QCityModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QCityModel(QObject *parent = nullptr);

    void setCities(const QStringList &aCityNames);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    int offsetOf(int row, int column) const;
    QStringList mCities;
    QVector<int> mDistances;
};

#endif // QCITYMODEL_H
