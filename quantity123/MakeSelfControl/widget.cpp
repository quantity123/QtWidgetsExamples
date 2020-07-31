#include "widget.h"
#include "./ui_widget.h"
#include <QScrollArea>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDebug>
#include "scrollareauserlist.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

///////////////////////////////////////////////用户列表/////////////////////////////////////////////////

//    QScrollArea *scrollArea = new QScrollArea(this);
//    scrollArea->resize(221, 451);
//    scrollArea->move(40, 60);
//    scrollArea->setWidgetResizable(true);
//    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    QWidget *widget = new QWidget(scrollArea);
//    scrollArea->setWidget(widget);

//    QVBoxLayout *gridLayout = new QVBoxLayout(widget);
//    gridLayout->setSpacing(0);
//    gridLayout->setMargin(0);
//    widget->setLayout(gridLayout);

//    for (int i=0; i<5; ++i)
//    {
//        QToolButton *tb = new QToolButton(widget);
//        tb->setIconSize(QSize(24, 24));
//        tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//        tb->setObjectName(QString::number(i));
//        tb->setIcon(QIcon("/home/quantity123/QTWorkspace/quantity123/AnyTalk/AnyTalkCli/AnyTalkHeadPortraitIcon/4kong.com-0001.png"));
//        tb->setText("自由星"+QString::number(i));
//        tb->setMinimumWidth(scrollArea->width());
//        tb->setEnabled(true);
//        gridLayout->addWidget(tb);
//    }
//    gridLayout->addStretch();


    QScrollAreaUserList *scrollAreaUserList = new QScrollAreaUserList(this);
    scrollAreaUserList->resize(this->width(), this->height());
//    scrollAreaUserList->move(300, 60);

    scrollAreaUserList->refresh();

    ui->horizontalLayout_2->addWidget(scrollAreaUserList);


///////////////////////////////////////////////聊天记录列表/////////////////////////////////////////////////


/*
<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'Ubuntu'; font-size:12pt; font-weight:600; color:#4e9a06;">[斧头帮]2020-06-11 12:12:12</span></p>
<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'Ubuntu'; font-size:12pt; color:#000000;">你好阿</span></p>
<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'Ubuntu'; font-size:12pt; font-weight:600; color:#4e9a06;">[青龙帮]2020-06-11 12:12:12</span></p>
<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" font-family:'Ubuntu';">谢谢你</span></p>
*/
//    ui->textEdit->append("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:12pt; font-weight:600; color:#4e9a06;\">[青龙帮]2020-06-11 12:12:12</span></p>");


}

Widget::~Widget()
{
    delete ui;
}

