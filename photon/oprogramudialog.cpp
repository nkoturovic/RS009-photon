#include "oprogramudialog.h"
#include "ui_oprogramudialog.h"

oProgramuDialog::oProgramuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oProgramuDialog)
{
    ui->setupUi(this);
}

oProgramuDialog::~oProgramuDialog()
{
    delete ui;
}
