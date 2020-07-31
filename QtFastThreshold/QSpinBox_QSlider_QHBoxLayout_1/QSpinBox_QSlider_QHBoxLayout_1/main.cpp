#include "mainwindow.h"
#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget widget;
    widget.setWindowTitle("Your Age:");
    QSpinBox spinBox;
    QSlider slider(Qt::Horizontal);
    spinBox.setRange(0, 100);
    slider.setRange(0, 100);
    QObject::connect(&spinBox, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    QObject::connect(&slider, SIGNAL(valueChanged(int)), &spinBox, SLOT(setValue(int)));
    spinBox.setValue(35);
    slider.setValue(35);
    QHBoxLayout layout;
    layout.addWidget(&spinBox);
    layout.addWidget(&slider);
    widget.setLayout(&layout);
    widget.show();
    return a.exec();
}
