#ifndef QQTTTREE_H
#define QQTTTREE_H

#include <QObject>
#include <QString>

class QQttTreeColumnsData : public QObject
{
    Q_OBJECT
public:
    enum TreeColumnsDataType
    {
        cdtName,
        cdtAreaSize,
        cdtPopulation,
    };
    explicit QQttTreeColumnsData(QObject *parent = nullptr);
    void setName(const QString &aName);
    const QString& name() const;
    void setAreaSize(const QString &aAreaSize);
    const QString& areaSize() const;
    void setPopulation(const QString &aPopulation);
    const QString& population() const;
//signals:
private:
    QString mPopulation;
    QString mAreaSize;
    QString mName;
};

#endif // QQTTTREE_H
