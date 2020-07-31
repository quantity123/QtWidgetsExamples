#include "qcoinflippushbtn.h"
#include <QDebug>

QCoinFlipPushBtn::QCoinFlipPushBtn(QString aNormalCoinImg)
{
    QPixmap pixmap;
    bool loadRet = pixmap.load(aNormalCoinImg);
    if (!loadRet)
    {
        qDebug() << aNormalCoinImg + "图片加载失败！";
        return;
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QIcon(pixmap));   //aNormalCoinImg传资源路径也可以
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    mTimer1.setParent(this);
    mTimer2.setParent(this);

    auto onTimerOut1 = [&]()
    {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1").arg(this->mMin++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (mMin > mMax)
        {
            mTimer1.stop();
            mMin = 1;
        }
    };
    connect(&mTimer1, &QTimer::timeout, onTimerOut1);

    auto onTimerOut2 = [&]()
    {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1").arg(this->mMax--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (mMax < mMin)
        {
            mTimer2.stop();
            mMax = 8;
        }
    };
    connect(&mTimer2, &QTimer::timeout, onTimerOut2);
}

void QCoinFlipPushBtn::setPosX(quint8 aX)
{
    mPosX = aX;
}

void QCoinFlipPushBtn::setPosY(quint8 aY)
{
    mPosY = aY;
}

void QCoinFlipPushBtn::setFlag(quint8 aFlag)
{
    mFlag = static_cast<bool>(aFlag);
}

void QCoinFlipPushBtn::changeFlag()
{
    if (this->mFlag)
    {
        mTimer1.start(30);
        this->mFlag = false;
    }
    else
    {
        mTimer2.start(30);
        this->mFlag = true;
    }
}

quint8 QCoinFlipPushBtn::posX() const
{
    return mPosX;
}

quint8 QCoinFlipPushBtn::posY() const
{
    return mPosY;
}

bool QCoinFlipPushBtn::flag() const
{
    return mFlag;
}
