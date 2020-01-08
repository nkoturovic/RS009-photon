#ifndef OPROGRAMUDIALOG_H
#define OPROGRAMUDIALOG_H

#include <QDialog>

namespace Ui {
class oProgramuDialog;
}

class oProgramuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit oProgramuDialog(QWidget *parent = nullptr);
    ~oProgramuDialog();

private:
    Ui::oProgramuDialog *ui;
};

#endif // OPROGRAMUDIALOG_H
