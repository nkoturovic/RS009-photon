#include "cropdialog.h"
#include "ui_cropdialog.h"

cropDialog::cropDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cropDialog)
{
    ui->setupUi(this);
}

cropDialog::~cropDialog()
{
    delete ui;
}
