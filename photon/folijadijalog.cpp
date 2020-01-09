#include "folijadijalog.h"
#include "ui_folijadijalog.h"

folijaDijalog::folijaDijalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::folijaDijalog)
{
    ui->setupUi(this);
}

folijaDijalog::~folijaDijalog()
{
    delete ui;
}

std::optional<rs::Overlay::Color> folijaDijalog::getColor() {
    folijaDijalog d;
    if (d.exec() == QDialog::Accepted) {
        std::string text = d.ui->folije->currentText().toStdString();
        if (text == "Crvena")
           return rs::Overlay::Color::RED;
        else if (text == "Zelena")
           return rs::Overlay::Color::GREEN;
        else
           return rs::Overlay::Color::BLUE;
    }
    return {};
}
