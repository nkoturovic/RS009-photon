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

private:
    Ui::photon_main *ui;
    PhotonUndo m_imageUndo;
};

#endif // PHOTON_MAIN_H


