#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qteacher.h"
#include "qstudent.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void callTeacharHungry1();
    void callTeacharHungry2();
    QTeacher *mTeacher;
    QStudent *mStudent;
};
#endif // WIDGET_H
