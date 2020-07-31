#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qwork.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void on_pushButton_clicked();

private:
    QImage mImage;
    QWork *mWork;
    Ui::Widget *ui;
};
#endif // WIDGET_H
