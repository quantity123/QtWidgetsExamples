#include <QApplication>
#include "talkwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(a.applicationDirPath() + "/AnyTalkClientIcon.png"));
    a.setWindowIcon(QIcon("AnyTalkClientIcon.png"));
    TalkWindow talkWindow;
    //talkWindow.show();
    return a.exec();
}
