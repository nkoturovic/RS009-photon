#include "photon_main.h"
#include "ui_photon_main.h"
#include <rsimg/exception.hpp>

photon_main::photon_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::photon_main)
{
    ui->setupUi(this);
}

photon_main::~photon_main()
{
    delete ui;
}


void photon_main::on_actionOtvori_triggered()
{
    try {
        this->m_imageUndo = PhotonUndo(rs::Image("lena.png"));
        ui->slika_glavno->setImage(m_imageUndo.qimagePtr());
        ui->slika_glavno->update();
    }  catch (const rs::Exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

}

void photon_main::on_actionRotacija_triggered()
{
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::LEFT));
    ui->slika_glavno->update();
}

void photon_main::on_actionPoni_ti_izmenu_undo_triggered()
{
    m_imageUndo.undo();
    ui->slika_glavno->update();
}
