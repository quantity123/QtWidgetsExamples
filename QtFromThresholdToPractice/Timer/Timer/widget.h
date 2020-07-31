#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimerEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void timerEvent(QTimerEvent *timeEvent);

private:
    Ui::Widget *ui;
    int mTimerId1;
    int mTimerId2;
    int mTimerId1Num;
    int mTimerId2Num;
    QTimer *mTimer;
    int mTimerId3Num;
};
#endif // WIDGET_H
