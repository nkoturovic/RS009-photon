#ifndef BRIGHTNESSDIALOG_H
#define BRIGHTNESSDIALOG_H

#include <QDialog>
#include <optional>

namespace Ui {
class brightnessDialog;
}

class brightnessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit brightnessDialog(QWidget *parent = nullptr);
    ~brightnessDialog();

    static std::optional<int> getSliderValue();

private:
    Ui::brightnessDialog *ui;
};

#endif // BRIGHTNESSDIALOG_H
