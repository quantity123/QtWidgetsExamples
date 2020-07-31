#ifndef QCOINFLIPPUSHBTN_H
#define QCOINFLIPPUSHBTN_H

#include <QPushButton>
#include <QTimer>

class QCoinFlipPushBtn : public QPushButton
{
    Q_OBJECT
public:
    //explicit QCoinFlipPushBtn(QPushButton *parent = nullptr, QString aNormalCoinImg="");
    QCoinFlipPushBtn(QString aNormalCoinImg);
    void setPosX(quint8 aX);
    void setPosY(quint8 aY);
    void setFlag(quint8 aFlag);
    //翻转硬币并改变标志
    void changeFlag();
    quint8 posX() const;
    quint8 posY() const;
    bool flag() const;
signals:
private:
    quint8 mPosX;
    quint8 mPosY;
    bool mFlag;  //金币正反标志
    QTimer mTimer1;  //正面翻反面定时器
    QTimer mTimer2;  //反面翻正面定时器
    quint8 mMin = 1;
    quint8 mMax = 8;
};

#endif // QCOINFLIPPUSHBTN_H
