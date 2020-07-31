#include "qqtttreecolumnsdata.h"

QQttTreeColumnsData::QQttTreeColumnsData(QObject *parent)
    : QObject(parent)
{
}

void QQttTreeColumnsData::setName(const QString &aName)
{
    mName = aName;
}

const QString& QQttTreeColumnsData::name() const
{
    return mName;
}

void QQttTreeColumnsData::setAreaSize(const QString &aAreaSize)
{
    mAreaSize = aAreaSize;
}

const QString& QQttTreeColumnsData::areaSize() const
{
    return mAreaSize;
}

void QQttTreeColumnsData::setPopulation(const QString &aPopulation)
{
    mPopulation = aPopulation;
}

const QString& QQttTreeColumnsData::population() const
{
    return mPopulation;
}
