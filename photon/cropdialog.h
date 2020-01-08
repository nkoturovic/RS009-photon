#ifndef CROPDIALOG_H
#define CROPDIALOG_H

#include <QDialog>

namespace Ui {
class cropDialog;
}

class cropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cropDialog(QWidget *parent = nullptr);
    ~cropDialog();

private:
    Ui::cropDialog *ui;
};

#endif // CROPDIALOG_H
