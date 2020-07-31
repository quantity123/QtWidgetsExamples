#include "mycontrol.h"
#include "ui_mycontrol.h"

MyControl::MyControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyControl)
{
    ui->setupUi(this);

    //spinBox移动，QSlider跟着移动
    void(QSpinBox:: *spValueChanged)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, spValueChanged, ui->horizontalSlider, &QSlider::setValue);

    //QSlider移动，spinBox跟着移动
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

MyControl::~MyControl()
{
    delete ui;
}

void MyControl::setPos(int aPos)
{
    ui->spinBox->setValue(aPos);
}

int MyControl::getPos() const
{
    return ui->spinBox->value();
}
