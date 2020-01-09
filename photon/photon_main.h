#ifndef PHOTON_MAIN_H
#define PHOTON_MAIN_H

#include <QMainWindow>
#include "photon_undo.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class photon_main; }
QT_END_NAMESPACE

class photon_main : public QMainWindow
{
    Q_OBJECT

public:
    photon_main(QWidget *parent = nullptr);
    ~photon_main();

private slots:
    void on_actionOtvori_triggered();

    void on_actionRotacija_triggered();

    void on_actionPoni_ti_izmenu_undo_triggered();

    void on_actionObrtanje_flip_triggered();

    void on_actionObrtanje_y_osa_triggered();

    void on_actionSe_enje_triggered();

    void on_actionOsvetljenje_triggered();

    void on_actionKontrast_triggered();

    void on_actionVrati_izmenu_redo_triggered();

    void on_actionIza_i_iz_programa_triggered();

    void on_primeni_clicked();

    void on_obrni_x_clicked();

    void on_actionSnimi_sa_uvaj_triggered();

    void on_plus_180_clicked();

    void on_plus_90_clicked();

    void on_minus_90_clicked();

    void on_obrni_y_clicked();

    void on_invertovanje_clicked();

    void on_crno_belo_clicked();

    void on_actionOd_tampaj_triggered();

    void on_actionCrno_belo_B_W_triggered();

    void on_actionInvertovanje_boja_triggered();

    void on_actionRotacija_ulevo_triggered();

    void on_actionRotacija_udesno_triggered();

    void on_actionAutori_triggered();

    void on_actionFolija_triggered();

    void on_actionZamu_enje_triggered();

    void on_actionCrte_triggered();

    void on_crtez_clicked();

    void on_actionSrebro_triggered();

    void on_actionLeto_triggered();

    void on_srebro_clicked();

    void on_leto_clicked();

    void on_actionZima_triggered();

    void on_zima_clicked();

    void on_actionDuga_triggered();

    void on_duga_clicked();

    void on_actionNeon_triggered();

    void on_neon_clicked();

    void on_actionSepia_triggered();

    void on_sepia_clicked();

    void on_sepia_2_clicked();

    void on_folija_clicked();

    void on_zamucenje_clicked();

private:
    Ui::photon_main *ui;
    PhotonUndo m_imageUndo;
};

#endif // PHOTON_MAIN_H


