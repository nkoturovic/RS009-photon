#include "photon_main.h"
#include "ui_photon_main.h"
#include <rsimg/exception.hpp>
#include <QFileDialog>

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
    QString nazivFajla = QFileDialog::getOpenFileName(this, "Otvorite fajl:");
    //QFile fajl(nazivFajla);

    try {
        this->m_imageUndo = PhotonUndo(rs::Image(nazivFajla.toStdString()));
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

void photon_main::on_actionObrtanje_flip_triggered()    //obrtanje po X osi
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::X));
    ui->slika_glavno->update();
}

void photon_main::on_actionObrtanje_y_osa_triggered()   //obrtanje po Y osi
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::Y));
    ui->slika_glavno->update();
}

void photon_main::on_actionSe_enje_triggered()
{
    m_imageUndo.action(rs::Crop(0,0,100,100));
    ui->slika_glavno->update();
}

void photon_main::on_actionOsvetljenje_triggered()
{
//TODO
}

void photon_main::on_actionKontrast_triggered()
{
    m_imageUndo.action(rs::Contrast(50)); //TODO kako uhvatiti podatak sa slajdera?
    ui->slika_glavno->update();
}

void photon_main::on_actionVrati_izmenu_redo_triggered()
{
    m_imageUndo.redo();
    ui->slika_glavno->update();
}

void photon_main::on_actionIza_i_iz_programa_triggered()
{
    QApplication::exit();
}

void photon_main::on_primeni_clicked()  //primenjuje se osvetljenje i kontrast
{
    m_imageUndo.action(rs::Brightness(ui->osvetljenje_slider->value()));
    m_imageUndo.action(rs::Contrast(ui->kontrast_slider->value()));
    ui->slika_glavno->update();
}

void photon_main::on_obrni_x_clicked()
{

}

void photon_main::on_actionSnimi_sa_uvaj_triggered()
{
    QString nazivFajla = QFileDialog::getSaveFileName(this, "Sačuvaj kao");
}
