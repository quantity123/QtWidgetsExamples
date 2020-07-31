#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mTreeView = new QTreeView(this);
    mTreeModel = new QMyTreeViewModel(this);
    mHeaderView = new QMyHeaderView(this);
    mTreeView->setFixedSize(400, 300);
    mTreeView->setModel(mTreeModel);
    mTreeView->setHeader(mHeaderView);
    mTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mTreeView->setExpandsOnDoubleClick(false);
    mTreeView->setIndentation(5);
    mTreeView->setColumnWidth(0, 150);
    mTreeView->setColumnWidth(1, 400);
    mTreeView->header()->setStretchLastSection(true);
    connect(mHeaderView, &QMyHeaderView::stateChanged, mTreeModel, &QMyTreeViewModel::slot_stateChanged);
    connect(mTreeModel, &QMyTreeViewModel::stateChanged, mHeaderView, &QMyHeaderView::slot_stateChanged);
    connect(mTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::slot_selectionChanged);
}

MainWindow::~MainWindow()
{
    delete mHeaderView;
    delete mTreeModel;
    delete mTreeView;
}

void MainWindow::slot_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    for (int i=0; i<selected.indexes().count(); ++i)
    {
        mTreeModel->setData(selected.indexes().at(i), Qt::Checked, Qt::UserRole+1);
    }
    for (int i=0; i<deselected.indexes().count(); ++i)
    {
        mTreeModel->setData(deselected.indexes().at(i), Qt::Unchecked, Qt::UserRole+1);
    }
}
