#include "qstartandbackpushbtn.h"
#include <QDebug>

QStartAndBackPushBtn::QStartAndBackPushBtn(QString aNormalPixmap, QString aPressPixmap)
{
    fNormalPixmap = aNormalPixmap;
    fPressPixmap = aPressPixmap;
    QPixmap pixmap;
    bool loadRet = pixmap.load(fNormalPixmap);
    if (!loadRet)
    {
        qDebug() << aNormalPixmap + "图片加载失败！";
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px};");
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    this->setIcon(QIcon(pixmap));

    //设置动画对象是哪个目标
    fStartBtnClickAnimation.setTargetObject(this);
    //设置动画属性类型
    fStartBtnClickAnimation.setPropertyName("geometry");
    //设置动画播放时间
    fStartBtnClickAnimation.setDuration(150);
    //设置动画缓缓移动曲线
    fStartBtnClickAnimation.setEasingCurve(QEasingCurve::OutBounce);
}

void QStartAndBackPushBtn::zoom(bool aIsDown)
{
    if (aIsDown)
    {
        //设置起始位置
        fStartBtnClickAnimation.setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
        //设置结束位置
        fStartBtnClickAnimation.setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
        //执行动画
        fStartBtnClickAnimation.start();
    }
    else
    {
        //设置起始位置
        fStartBtnClickAnimation.setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
        //设置结束位置
        fStartBtnClickAnimation.setEndValue(QRect(this->x(), this->y()-10, this->width(), this->height()));
        //执行动画
        fStartBtnClickAnimation.start();
    }
}

void QStartAndBackPushBtn::mousePressEvent(QMouseEvent *e)
{
    if (fPressPixmap != "")
    {
        QPixmap pixmap;
        bool loadRet = pixmap.load(fPressPixmap);
        if (!loadRet)
        {
            qDebug() << fPressPixmap + "图片加载失败！";
            return;
        }
        //this->setFixedSize(pixmap.width(), pixmap.height());  //初始化已经把图像一些参数设置好，这里不用设置
        //this->setStyleSheet("QPushButton{border:0px};");
        //this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        this->setIcon(QIcon(pixmap));
    }
    return QPushButton::mousePressEvent(e);
}

void QStartAndBackPushBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if (fPressPixmap != "")
    {
        QPixmap pixmap;
        bool loadRet = pixmap.load(fNormalPixmap);
        if (!loadRet)
        {
            qDebug() << fNormalPixmap + "图片加载失败！";
            return;
        }
        this->setIcon(QIcon(pixmap));
    }
    return QPushButton::mouseReleaseEvent(e);
}
