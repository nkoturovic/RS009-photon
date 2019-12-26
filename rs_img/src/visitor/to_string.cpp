#include "../../include/rsimg/visitor/to_string.hpp"

std::string rounded(std::string str) { return str.substr(0, str.find(".")); };

namespace rs::visitor {

void ToString::visit(const rs::Composition &comp) {
    ToString toStr;
    std::string fst = toStr(comp.firstTransform());
    std::string snd = toStr(comp.secondTransform());

    result("Composition(" + fst + "," + snd + ")");
}

void ToString::visit(const rs::Rotate &rot) {
    std::string tmp = "Rotate(";
    tmp += rot.direction() == rs::Rotate::Direction::LEFT ? "LEFT" : "RIGHT";
    tmp += ")";
    result(std::move(tmp));
}

void ToString::visit(const rs::Flip &flp) {
    std::string tmp = "Flip(";
    tmp += flp.axis() == rs::Flip::Axis::X ? "X" : "Y";
    tmp += ")";
    result(std::move(tmp));
}

void ToString::visit(const rs::BlackNWhite &) {
    result("B&W");
}
void ToString::visit(const rs::Brightness &br) {
    result("Brightness(" + rounded(std::to_string(br.percents())) + ")");
}

void ToString::visit(const rs::Contrast &ct) {
    result("Contrast(" + rounded(std::to_string(ct.percents())) + ")");
}
void ToString::visit(const rs::Crop &cr) {

    result("Crop(" +
                   rounded(std::to_string(cr.x()))
                    + "," +
                   rounded(std::to_string(cr.y()))
                    + "," +
                   rounded(std::to_string(cr.width()))
                    + "," +
                   rounded(std::to_string(cr.height()))
                    + ")");
}
} // ns rs
