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
