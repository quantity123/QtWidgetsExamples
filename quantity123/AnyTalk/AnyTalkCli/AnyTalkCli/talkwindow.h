#ifndef TALKWINDOW_H
#define TALKWINDOW_H

#include <QMainWindow>
#include "scrollareauserlist.h"
#include "loginwindow.h"

namespace Ui {
class TalkWindow;
}

class TalkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TalkWindow(QWidget *parent = nullptr);
    ~TalkWindow();

private:
    LoginWindow *mLoginWindow;
    QScrollAreaUserList *mUserListScrollArea;
    Ui::TalkWindow *ui;
};

#endif // TALKWINDOW_H
