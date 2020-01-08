#include "contrastdialog.h"
#include "ui_contrastdialog.h"

contrastDialog::contrastDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contrastDialog)
{
    ui->setupUi(this);
}

contrastDialog::~contrastDialog()
{
    delete ui;
}

std::optional<int> contrastDialog::getSliderValue() {
    contrastDialog d;
    if (d.exec() == QDialog::Accepted)
        return d.ui->horizontalSlider->value();
    else 
        return {};
}
