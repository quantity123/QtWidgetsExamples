#ifndef QCURRENCYMODEL_H
#define QCURRENCYMODEL_H

#include <QAbstractTableModel>

class QCurrencyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QCurrencyModel(QObject *parent = nullptr);
    void setCurrencyMap(const QMap<QString, double> &aCurrencyMap);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
    QString at(int offset) const;
    QMap<QString, double> mCurrencyMap;
};

#endif // QCURRENCYMODEL_H
