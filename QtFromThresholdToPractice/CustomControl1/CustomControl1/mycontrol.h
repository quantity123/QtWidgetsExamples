#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QWidget>

namespace Ui {
class MyControl;
}

class MyControl : public QWidget
{
    Q_OBJECT

public:
    explicit MyControl(QWidget *parent = nullptr);
    ~MyControl();
    void setPos(int aPos);
    int getPos() const;
private:
    Ui::MyControl *ui;
};

#endif // MYCONTROL_H
