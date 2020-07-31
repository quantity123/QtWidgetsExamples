#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createTextEdit();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createActions();
private slots:
    void slotFileNew();
    void slotFileOpen();
    void slotFileSave();
    void slotCopy();
    void slotCut();
    void slotPaste();
    void slotAbout();
private:
    QTextEdit *mTextEdit;
    QMenuBar *mMenuBar;
    QMenu *mFileMenu;
    QMenu *mEditMenu;
    QMenu *mAboutMenu;
    QAction *mFileNewAction;
    QAction *mFileOpenAction;
    QAction *mFileSaveAction;
    QAction *mExitAction;
    QAction *mCopyAction;
    QAction *mCutAction;
    QAction *mPasteAction;
    QAction *mAboutAction;
};
#endif // MAINWINDOW_H
