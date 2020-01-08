#include "custom_visitors.hpp"

#include <QPixmap>
#include <QImage>

std::string rounded(std::string str) { return str.substr(0, str.find(".")); };

void ToStringSR::visit(const rs::Composition &comp) {
    ToStringSR toStr;
    std::string fst = toStr(comp.firstTransform());
    std::string snd = toStr(comp.secondTransform());

    result("Kompozicija(" + fst + "," + snd + ")");
}

void ToStringSR::visit(const rs::Rotate &rot) {
    std::string tmp = "Rotacija(";
    tmp += rot.direction() == rs::Rotate::Direction::LEFT ? "LEVO" : "DESNO";
    tmp += ")";
    result(std::move(tmp));
}

void ToStringSR::visit(const rs::Flip &flp) {
    std::string tmp = "Obrtanje(";
    tmp += flp.axis() == rs::Flip::Axis::X ? "X" : "Y";
    tmp += ")";
    result(std::move(tmp));
}

void ToStringSR::visit(const rs::BlackNWhite &) {
    result("Crno-Belo");
}

void ToStringSR::visit(const rs::Invert &) {
    result("Invertovanje boja");
}

void ToStringSR::visit(const rs::Brightness &br) {
    result("Osvetljenje(" + rounded(std::to_string(br.percents())) + ")");
}

void ToStringSR::visit(const rs::Contrast &ct) {
    result("Kontrast(" + rounded(std::to_string(ct.percents())) + ")");
}
void ToStringSR::visit(const rs::Crop &cr) {

    result("Secenje(" +
                   rounded(std::to_string(cr.x()))
                    + "," +
                   rounded(std::to_string(cr.y()))
                    + "," +
                   rounded(std::to_string(cr.width()))
                    + "," +
                   rounded(std::to_string(cr.height()))
                    + ")");
}

void ToStringSR::otherwise(const rs::Transform &) {
    result("Druga transformacija");
}


void UndoItemGenerator::visit(const rs::Composition &comp) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rotate.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(comp));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Rotate &rot) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rotate.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(rot));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Flip &flp) {
    static QPixmap pixMapX = QPixmap::fromImage(QImage(":pngs/icons/flip_x.png"));
    static QPixmap pixMapY = QPixmap::fromImage(QImage(":pngs/icons/flip_y.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(flp));

    if (flp.axis() == rs::Flip::Axis::X) {
        result(new UndoItem(m_parentPtr, pixMapX, std::move(str)));
    } else {
        result(new UndoItem(m_parentPtr, pixMapY, std::move(str)));
    }
}

void UndoItemGenerator::visit(const rs::BlackNWhite &bw) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/black_white.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(bw));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Brightness &br) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/brightness.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(br));

    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Contrast &ct) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/contrast.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(ct));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Crop &cr) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/crop.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(cr));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Invert &inv) {
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(inv));
    result(new UndoItem(m_parentPtr, QPixmap::fromImage(QImage(":pngs/icons/invert.png")), std::move(str)));
}

void UndoItemGenerator::otherwise(const rs::Transform &t) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rotate.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(t));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}
