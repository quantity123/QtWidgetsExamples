#ifndef QCOMMDATA_H
#define QCOMMDATA_H

#include <QObject>

class QCommData : public QObject
{
    Q_OBJECT
public:
    explicit QCommData(QObject *parent = nullptr);
public slots:
    void setCommonData(qint32 aData);
    int commonData() const;
private:
    qint32 mCommonData;
};

#endif // QCOMMDATA_H
