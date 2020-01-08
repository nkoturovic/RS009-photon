#include "brightnessdialog.h"
#include "ui_brightnessdialog.h"

brightnessDialog::brightnessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::brightnessDialog)
{
    ui->setupUi(this);
}

brightnessDialog::~brightnessDialog()
{
    delete ui;
}

std::optional<int> brightnessDialog::getSliderValue() {
    brightnessDialog d;
    if (d.exec() == QDialog::Accepted)
        return d.ui->horizontalSlider->value();
    else 
        return {};
}
