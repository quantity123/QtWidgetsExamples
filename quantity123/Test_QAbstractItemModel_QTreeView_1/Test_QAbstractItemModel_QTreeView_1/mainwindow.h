#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "qmyheaderview.h"
#include "qmytreeviewmodel.h"
#include <QTreeView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slot_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    QMyHeaderView *mHeaderView;
    QMyTreeViewModel *mTreeModel;
    QTreeView *mTreeView;
};
#endif // MAINWINDOW_H
