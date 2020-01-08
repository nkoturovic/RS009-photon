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

std::optional<cropDialog::CropReturnType> cropDialog::getValues() {
    cropDialog d;
    int code = d.exec();
    if (code == QDialog::Accepted) {
        try {
            return cropDialog::CropReturnType {
                .x = std::stoi(d.ui->xKoord->text().toStdString()),
                .y = std::stoi(d.ui->yKoord->text().toStdString()),
                .width = std::stoi(d.ui->sirina->text().toStdString()),
                .height = std::stoi(d.ui->visina->text().toStdString())
            };
        } catch (...) {
            return {};
        }
    } else {
        return {};
    }
}
