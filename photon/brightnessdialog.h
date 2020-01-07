#ifndef BRIGHTNESSDIALOG_H
#define BRIGHTNESSDIALOG_H

#include <QDialog>

namespace Ui {
class brightnessDialog;
}

class brightnessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit brightnessDialog(QWidget *parent = nullptr);
    ~brightnessDialog();

private:
    Ui::brightnessDialog *ui;
};

#endif // BRIGHTNESSDIALOG_H
