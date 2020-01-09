#ifndef FOLIJADIJALOG_H
#define FOLIJADIJALOG_H

#include <optional>
#include <QDialog>
#include <rsimg/transform.hpp>

namespace Ui {
class folijaDijalog;
}

class folijaDijalog : public QDialog
{
    Q_OBJECT

public:
    explicit folijaDijalog(QWidget *parent = nullptr);
    ~folijaDijalog();

    static std::optional<rs::Overlay::Color> getColor();

private:
    Ui::folijaDijalog *ui;
};

#endif // FOLIJADIJALOG_H
