#include "talkwindow.h"
#include "./ui_talkwindow.h"
#include <QDesktopWidget>

TalkWindow::TalkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TalkWindow)
{
    ui->setupUi(this);

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);

    setWindowTitle("欢迎来到任意聊");

    mUserListScrollArea = new QScrollAreaUserList(ui->userListWidget);
    int width = ui->userListWidget->width();
    int heidht = ui->userListWidget->height();
    mUserListScrollArea->resize(width, heidht);
    ui->userListLayout->addWidget(mUserListScrollArea);
    mUserListScrollArea->refresh();

    ui->outputTextEdit->append("<p style=\" margin:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:600; color:#4e9a06;\">[青龙帮]2020-06-11 12:12:12</span></p>");
    ui->outputTextEdit->append("<p style=\" margin:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt; color:#000000;\">你好阿</span></p>");

    mLoginWindow = new LoginWindow(this);
    mLoginWindow->show();
}

TalkWindow::~TalkWindow()
{
    delete mLoginWindow;
    delete mUserListScrollArea;
    google::protobuf::ShutdownProtobufLibrary();
    delete ui;
}
