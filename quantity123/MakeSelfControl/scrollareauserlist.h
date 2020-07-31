#ifndef SCROLLAREAUSERLIST_H
#define SCROLLAREAUSERLIST_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QToolButton>

using namespace std;

class QScrollAreaUserList : public QScrollArea
{
    Q_OBJECT

public:
    explicit QScrollAreaUserList(QWidget *parent = nullptr);
    ~QScrollAreaUserList();
    void refresh() const;
    void clearUserList() const;
    void buildUserList() const;
private:

    void addUser(const QString &aObjectName, const QIcon &aIcon, const QString &aText, int aMinimumWidth, bool aEnable) const;
    QWidget *mWidgetUserList;
    QVBoxLayout *mVBoxLayoutUserList;
};

#endif // SCROLLAREAUSERLIST_H
