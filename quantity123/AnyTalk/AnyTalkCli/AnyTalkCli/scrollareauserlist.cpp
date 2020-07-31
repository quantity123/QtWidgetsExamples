#include "scrollareauserlist.h"

QScrollAreaUserList::QScrollAreaUserList(QWidget *parent)
    : QScrollArea(parent)
{
    this->setWidgetResizable(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mWidgetUserList = new QWidget(this);
    this->setWidget(mWidgetUserList);
    mVBoxLayoutUserList = new QVBoxLayout(mWidgetUserList);
    mVBoxLayoutUserList->setSpacing(0);
    mVBoxLayoutUserList->setMargin(0);
    mWidgetUserList->setLayout(mVBoxLayoutUserList);
}

QScrollAreaUserList::~QScrollAreaUserList()
{
    delete mVBoxLayoutUserList;
    delete mWidgetUserList;
}

void QScrollAreaUserList::refresh() const
{
    clearUserList();
    buildUserList();

    //单个删除widget方法1，while循环删除
	//auto item = mVBoxLayoutUserList->takeAt(0);
	//delete item->widget();

    //单个删除widget方法2
    //mVBoxLayoutUserList->removeWidget(tbtmp);
    //delete tbtmp;
    
    //删除所有widget方法1，layout也删除
    //qDeleteAll(mWidgetUserList->children());
    //删除所有widget方法2，layout也删除
    //mWidgetUserList->deleteLater();
}

void QScrollAreaUserList::clearUserList() const
{
    while (mVBoxLayoutUserList->count() > 0)
    {
        auto userItem = mVBoxLayoutUserList->takeAt(0);
        delete userItem->widget();
    }
}

void QScrollAreaUserList::buildUserList() const
{
    for (int i=0; i<5; ++i)
    {
        QIcon icon(QIcon("/home/quantity123/QTWorkspace/quantity123/AnyTalk/AnyTalkCli/AnyTalkUserIcon/4kong.com-0001.png"));
        addUser(QString::number(i), icon, "自由星", this->width(), true);
    }
    mVBoxLayoutUserList->addStretch();
}

void QScrollAreaUserList::addUser(const QString &aObjectName, const QIcon &aIcon, const QString &aText, int aMinimumWidth, bool aEnable) const
{
    auto tb = new QToolButton(mWidgetUserList);
    tb->setIconSize(QSize(24, 24));
    tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb->setObjectName(aObjectName);
    tb->setIcon(aIcon);
    tb->setText(aText+aObjectName);
    tb->setMinimumWidth(aMinimumWidth);
    tb->setEnabled(aEnable);
    mVBoxLayoutUserList->addWidget(tb);
}
