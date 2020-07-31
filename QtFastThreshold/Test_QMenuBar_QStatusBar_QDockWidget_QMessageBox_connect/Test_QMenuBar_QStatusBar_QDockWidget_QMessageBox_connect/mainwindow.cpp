#include "mainwindow.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qtt Main Window");
    this->resize(600, 400);
    createActions();
    createTextEdit();
    createMenus();

    //QStatusBar *stBar = new QStatusBar(this);
    QStatusBar *stBar = statusBar();
    setStatusBar(stBar);    //set***的只能有一个
    QLabel *label1 = new QLabel("aaa");
    stBar->addWidget(label1);           //label放左侧，add***的可以有多个
    QLabel *label2 = new QLabel("bbb");
    stBar->addPermanentWidget(label2);  //label放右侧

    //浮动窗口
    QDockWidget *dockWidget = new QDockWidget("浮动窗口1");
    dockWidget->resize(300, 150);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createTextEdit()
{
    mTextEdit = new QTextEdit(this);
    //setCentralWidget(mTextEdit);  //设置中心部件，只能有一个
    mTextEdit->resize(400, 150);
    mTextEdit->move(35, 60);
}

void MainWindow::createMenus()
{
    mMenuBar = new QMenuBar(this);
    mMenuBar->setGeometry(0, 0, this->width(), 30);
    mFileMenu = mMenuBar->addMenu(tr("文件"));
    mFileMenu->addAction(mFileOpenAction);  //增加文件菜单子项
}

void MainWindow::createToolBars()
{

}

void MainWindow::createStatusBar()
{

}

void MainWindow::createActions()
{
    QIcon fileOpenIcon(":/images/open.png");
    mFileOpenAction = new QAction(fileOpenIcon, tr("打开"), this);
    mFileOpenAction->setShortcut(tr("Ctrl+0"));
    //mFileOpenAction->setEnabled(false);
    //QT4的方式连接
    //connect(mFileOpenAction, SIGNAL(triggered()), this, SLOT(slotFileOpen()));
    //QT5的方式连接
    connect(mFileOpenAction, &QAction::triggered, this, &MainWindow::slotFileOpen); //QAction(mFileOpenAction)里的信号，对应MainWindow(this)里的槽函数slotFileOpen
}

void MainWindow::slotFileNew()
{

}

void MainWindow::slotFileOpen()
{
    QMessageBox msgBox;
    msgBox.setText(tr("文件打开"));
    msgBox.exec();
}

void MainWindow::slotFileSave()
{

}

void MainWindow::slotCopy()
{

}

void MainWindow::slotCut()
{

}

void MainWindow::slotPaste()
{

}

void MainWindow::slotAbout()
{

}
