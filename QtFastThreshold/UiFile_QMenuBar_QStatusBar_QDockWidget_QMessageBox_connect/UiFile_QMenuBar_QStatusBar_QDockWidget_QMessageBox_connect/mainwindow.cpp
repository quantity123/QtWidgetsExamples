#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    move(400, 200);
    resize(600, 400);
    mLable = new QLabel("ready");
    ui->statusbar->addWidget(mLable);

    ui->action_C->setIcon(QIcon(":/images/copy.png"));  //用代码方式关联工具栏按钮和资源图片
    //ui->action_C->setEnabled(false);
    ui->action_X->setIcon(QIcon("/home/quantity123/QTWorkspace/QtFastThreshold/demo3/images/cut.png")); //用代码方式关联工具栏按钮和资源图片文件
}

MainWindow::~MainWindow()
{
    delete mLable;
    delete ui;
}


void MainWindow::on_action_N_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("triggered"));
    msgBox.exec();
    qDebug() << "triggered";
}

void MainWindow::on_action_O_triggered()
{
    QDialog *modalDlg = new QDialog(this);
    modalDlg->exec();
    delete modalDlg;
}

void MainWindow::on_action_S_triggered()
{
    QDialog *unModalDlg = new QDialog(this);
    unModalDlg->show();
}

void MainWindow::on_action_C_triggered()
{
    QMessageBox::critical(this, "标题", "文本");    //危险的消息对话框
    QMessageBox::information(this, "info", "信息");   //信息的消息对话框
    //参数1：父亲，参数2：标题，参数3：提示内容，参数4：哪些类型按钮，参数5：默认焦点在哪个按钮上
    auto selRet = QMessageBox::question(this, "ques", "提问", QMessageBox::Save|QMessageBox::Cancel, QMessageBox::Cancel);
    if (selRet == QMessageBox::Save)
    {
        qDebug() << "选择的是保存";
    }
    else
    {
        qDebug() << "选择的是取消";
    }
    QMessageBox::warning(this, "warning", "警告");    //警告的消息对话框
    QColor color = QColorDialog::getColor(QColor(255, 0, 0));   //选择颜色对话框
    qDebug() << "r =" << color.red() << ", g =" << color.green() << ", b =" << color.blue();
    QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "/home/quantity123", "*.profile");    //打开文件对话框
    qDebug() << filePath;
    bool b = false;
    QFont font = QFontDialog::getFont(&b, QFont("花文彩云", 36));
    if (b)
    {
        qDebug() << "b = true";
        qDebug() << "字体：" << font.family().toUtf8().data() << "字号：" << font.pointSize() << " 是否加粗" << font.bold() << "是否倾斜：" << font.italic();
    }
    else
    {
        qDebug() << "b = false";
        qDebug() << "字体：" << font.family().toUtf8().data() << "字号：" << font.pointSize() << " 是否加粗" << font.bold() << "是否倾斜：" << font.italic();
    }
}
