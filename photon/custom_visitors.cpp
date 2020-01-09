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

void ToStringSR::visit(const rs::Cartoon&) {
    result("Crtez");
}

void ToStringSR::visit(const rs::Overlay&) {
    result("Folija");
}

void ToStringSR::visit(const rs::Blur& tform) {
    result("Zamucenje(" + rounded(std::to_string(tform.percent())) + ")");
}

void ToStringSR::visit(const rs::Neon&) {
    result("Neon");
}

void ToStringSR::visit(const rs::Winter&) {
    result("Zima");
}

void ToStringSR::visit(const rs::Summer&) {
    result("Leto");
}

void ToStringSR::visit(const rs::Rainbow&) {
    result("Duga");
}

void ToStringSR::visit(const rs::Silver&) {
    result("Srebro");
}

void ToStringSR::visit(const rs::Sepia&) {
    result("Sepia");
}

void UndoItemGenerator::visit(const rs::Composition &comp) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rotate.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(comp));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Rotate &rot) {
    static QPixmap pixMapLeft = QPixmap::fromImage(QImage(":pngs/icons/left.png"));
    static QPixmap pixMapRight = QPixmap::fromImage(QImage(":pngs/icons/right.png"));

    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(rot));

    if(rot.direction()==rs::Rotate::Direction::LEFT)
        result(new UndoItem(m_parentPtr, pixMapLeft, std::move(str)));
    else
        result(new UndoItem(m_parentPtr, pixMapRight, std::move(str)));
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

void UndoItemGenerator::visit(const rs::Cartoon& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/cartoon.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Overlay& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rgb.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Blur& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/blur.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Neon& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/neon.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Winter& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/winter.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Summer& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/summer.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Rainbow& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/rainbow.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Silver& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/silver.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}

void UndoItemGenerator::visit(const rs::Sepia& tform) {
    static QPixmap pixMap = QPixmap::fromImage(QImage(":pngs/icons/sepia.png"));
    ToStringSR toStr;
    QString str = QString::fromStdString(toStr(tform));
    result(new UndoItem(m_parentPtr, pixMap, std::move(str)));
}
