#include "blurdialog.h"
#include "ui_blurdialog.h"

blurDialog::blurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::blurDialog)
{
    ui->setupUi(this);
}

blurDialog::~blurDialog()
{
    delete ui;
}


std::optional<int> blurDialog::getSliderValue() {
    blurDialog d;
    if (d.exec() == QDialog::Accepted)
        return d.ui->horizontalSlider->value();
    else
        return {};
}
