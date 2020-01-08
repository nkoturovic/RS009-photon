#ifndef CONTRASTDIALOG_H
#define CONTRASTDIALOG_H

#include <QDialog>

namespace Ui {
class contrastDialog;
}

class contrastDialog : public QDialog
{
    Q_OBJECT

public:
    explicit contrastDialog(QWidget *parent = nullptr);
    ~contrastDialog();
    static std::optional<int> getSliderValue();

private:
    Ui::contrastDialog *ui;
};

#endif // CONTRASTDIALOG_H
