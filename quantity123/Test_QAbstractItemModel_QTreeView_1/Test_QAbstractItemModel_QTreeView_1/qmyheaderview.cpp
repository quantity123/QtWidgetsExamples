#include "qmyheaderview.h"
#include <QPainter>
#include <QMouseEvent>

QMyHeaderView::QMyHeaderView(QWidget *parent)
    : QHeaderView(Qt::Orientation::Horizontal, parent)
{
    mState = Qt::Unchecked;
    mIsPressed = false;
    setSectionsClickable(true);
}

void QMyHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex); //绘制其它section
//    this->paintSection(painter, rect, logicalIndex);
    painter->restore();
    //绘制背景色
    painter->save();
    painter->setBrush(QBrush(Qt::gray));
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect);
    //绘制section的Text
    painter->setFont(QFont("SimSun", 12));
    painter->setPen(QColor("#000000"));
    painter->drawText(rect, Qt::AlignCenter, model()->headerData(logicalIndex, Qt::Horizontal).toString());
    painter->restore();
    //为第一列绘制checkbox
    if (logicalIndex == 0)
    {
        QStyleOptionButton option;
        option.initFrom(this);
        if (mState == Qt::Unchecked)
        {
            option.state |= QStyle::State_Off;
        }
        else if (mState == Qt::PartiallyChecked)
        {
            option.state |= QStyle::State_NoChange;
        }
        else if (mState == Qt::Checked)
        {
            option.state |= QStyle::State_On;
        }
        option.iconSize = QSize(20, 20);
        auto leftTopPoint = QPoint(rect.left()+5, rect.top()+(rect.height()-20)/2);
        auto rightBottomPoint = QPoint(rect.left()+25, rect.bottom()-(rect.height()-20)/2);
        option.rect = QRect(leftTopPoint, rightBottomPoint);
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
    }
}

void QMyHeaderView::mousePressEvent(QMouseEvent *e)
{
    int nColumn = logicalIndexAt(e->pos());
    if ((e->buttons()&Qt::LeftButton) && (nColumn==0))
    {
        mIsPressed = true;
        e->accept();
    }
    e->ignore();
}

void QMyHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
    if (mIsPressed)
    {
        if (mState == Qt::Unchecked)
        {
            mState = Qt::Checked;
        }
        else
        {
            mState = Qt::Unchecked;
        }
        updateSection(0);
        emit stateChanged(mState);  //状态改变
    }
    mIsPressed = false;
    e->accept();
}

void QMyHeaderView::slot_stateChanged(Qt::CheckState state)
{
    mState = state;
    updateSection(0);
}
