#include "photon_main.h"
#include "ui_photon_main.h"
#include <rsimg/exception.hpp>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QMessageBox>
#include "brightnessdialog.h"
#include "contrastdialog.h"

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

    // Ako je odabrano Cancel u dijalogu
    if(nazivFajla.isEmpty() || nazivFajla.isNull())
        return;

    try {
        this->m_imageUndo = PhotonUndo(rs::Image(nazivFajla.toStdString()), ui->slika, ui->istorija);
        ui->slika->update();
    }  catch (const rs::Exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

}

void photon_main::on_actionRotacija_triggered()
{
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::LEFT));
    ui->slika->update();
}

void photon_main::on_actionPoni_ti_izmenu_undo_triggered()  //UNDO
{
    m_imageUndo.undo();
    ui->slika->update();
}

void photon_main::on_actionObrtanje_flip_triggered()    //obrtanje po X osi
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::X));
    ui->slika->update();
}

void photon_main::on_actionObrtanje_y_osa_triggered()   //obrtanje po Y osi
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::Y));
    ui->slika->update();
}

void photon_main::on_actionSe_enje_triggered()
{
    m_imageUndo.action(rs::Crop(0,0,100,100));          //TODO
    ui->slika->update();
}

void photon_main::on_actionOsvetljenje_triggered()
{
    brightnessDialog b;
    b.show();
}

void photon_main::on_actionKontrast_triggered()
{
    contrastDialog c;
    c.show();
}

void photon_main::on_actionVrati_izmenu_redo_triggered()
{
    m_imageUndo.redo();
    ui->slika->update();
}

void photon_main::on_actionIza_i_iz_programa_triggered()
{
    QApplication::exit();
}

void photon_main::on_primeni_clicked()  //primenjuje se osvetljenje i kontrast
{/*
    m_imageUndo.action(rs::Brightness(ui->osvetljenje_slider->value()));
    m_imageUndo.action(rs::Contrast(ui->kontrast_slider->value()));
    ui->slika->update();
    */
}

void photon_main::on_obrni_x_clicked()
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::X));
    ui->slika->update();
}

void photon_main::on_actionSnimi_sa_uvaj_triggered()
{
    QString nazivFajla = QFileDialog::getSaveFileName(this, "Sačuvaj kao");
}

void photon_main::on_plus_180_clicked()
{
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::LEFT));
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::LEFT));
    ui->slika->update();
}

void photon_main::on_plus_90_clicked()
{
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::RIGHT));
    ui->slika->update();
}

void photon_main::on_minus_90_clicked()
{
    m_imageUndo.action(rs::Rotate(rs::Rotate::Direction::LEFT));
    ui->slika->update();
}

void photon_main::on_obrni_y_clicked()
{
    m_imageUndo.action(rs::Flip(rs::Flip::Axis::Y));
    ui->slika->update();
}

void photon_main::on_invertovanje_clicked()
{
    m_imageUndo.action(rs::Invert());
    ui->slika->update();
}

void photon_main::on_crno_belo_clicked()
{
    m_imageUndo.action(rs::BlackNWhite());
    ui->slika->update();
}

void photon_main::on_actionOd_tampaj_triggered()
{
    QPrinter stampac1;
        stampac1.setPrinterName("Naziv stampaca");
        QPrintDialog dialog(&stampac1,this);
        if(dialog.exec() == QDialog::Rejected){
            QMessageBox::warning(this,"Upozorenje","Nije moguce pristupiti stampacu");
            return;
        }
        //ui->slika->print(&stampac1);
}

void photon_main::on_actionCrno_belo_B_W_triggered()
{
    m_imageUndo.action(rs::BlackNWhite());
    ui->slika->update();
}

void photon_main::on_actionInvertovanje_boja_triggered()
{
    m_imageUndo.action(rs::Invert());
    ui->slika->update();
}
