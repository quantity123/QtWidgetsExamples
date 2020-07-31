#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmylineedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLineEdit *lineEdit = new QLineEdit(this->centralWidget());
    lineEdit->move(10, 80);
    lineEdit->setText("QLineEdit");
    QMyLineEdit *myLineEdit = new QMyLineEdit(this);
//    myLineEdit->setFixedSize(400, 200);
    myLineEdit->move(10, 150);
    myLineEdit->setText("QMyLineEdit");

    QString styleSheet;

    //通用选择器：把所有控件背景设置成黄色，* 是通配符所有
//    styleSheet = "* {background-color:yellow;}";

    //类型选择器：把QWidget类背景设置成黄色，继承的子类也会被作用
    //多个类型选择器都可以用","分隔
//    styleSheet = "QWidget {background-color:yellow;}";

    //类选择器：仅仅作用于本类
//    styleSheet = ".QWidget {background-color:yellow;}";
    //多个类选择器用","分隔
//    styleSheet += ".QLineEdit {background-color:yellow;}";   //类选择器：仅仅作用于本类
//    styleSheet += ".QMyLineEdit {background-color:yellow;}";
//    styleSheet += ".QLineEdit, .QMyLineEdit {background-color:yellow;}";

    //对象选择器(#+objectName)，只作用于上面设置的 lineEdit 对象名称
    //多个对象选择器可以用","分隔
//    ui->lineEdit->setObjectName("lineEdit333");
//    myLineEdit->setObjectName("lineEdit444");
//    styleSheet += "#lineEdit333 {background-color:yellow;}";
//    styleSheet += "#lineEdit333, #lineEdit444 {background-color:yellow;}";

    //属性选择器，属性bkColor和值'red'要一一对应，否则无效
//    styleSheet += "QLineEdit[bkColor='red'] {background-color:red;}";
//    styleSheet += "QLineEdit[bkColor='green'] {background-color:green;}";
//    ui->lineEdit->setProperty("bkColor", "red");
//    myLineEdit->setProperty("bkColor", "green");

    //包含选择器：作用于父控件下所有指定的类型的间接子控件(父类是this->centralWidget())和直接子控件(父类是this)
//    styleSheet = "QMainWindow QLineEdit {background-color:green;}";
    //子元素选择器：不作用于父控件下所有指定的类型的间接子控件(父类是this->centralWidget())，作用于直接子控件(父类是this)
//    styleSheet = "QMainWindow > QLineEdit {background-color:green;}";

    //伪类选择器：格式是 选择器:状态，支持 非操作符 !
//    styleSheet += "QPushButton:pressed {color: red;}";
//    styleSheet += "QPushButton:!pressed {color: green;}";
    //链式规则："选择器:状态1:状态2:状态3"，状态之间使用逻辑与，同时满足条件样式才生效
//    styleSheet += "QPushButton:hover:pressed {color: yellow;}";
//    styleSheet += "QPushButton:pressed {color: yellow;}";



    qApp->setStyleSheet(styleSheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}

