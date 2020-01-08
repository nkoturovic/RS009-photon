#ifndef CROPDIALOG_H
#define CROPDIALOG_H

#include <QDialog>
#include <optional>

namespace Ui {
class cropDialog;
}

class cropDialog : public QDialog
{
    Q_OBJECT

public:
    struct CropReturnType {
        int x, y, width, height;
    };

    explicit cropDialog(QWidget *parent = nullptr);
    ~cropDialog();

    static std::optional<CropReturnType> getValues();

private:
    Ui::cropDialog *ui;
};

#endif // CROPDIALOG_H
