#include "../../include/rsimg/visitor/to_string.hpp"

std::string rounded(std::string str) { return str.substr(0, str.find(".")); };

namespace rs::visitor {

void toString::visit(const rs::Composition &comp) {
    std::string fst = toString(comp.firstTransform());
    std::string snd = toString(comp.secondTransform());

    m_result_str = "Composition(" + fst + "," + snd + ")";
}

void toString::visit(const rs::Rotate &rot) {
    m_result_str = "Rotate(";
    m_result_str += rot.direction() == rs::Rotate::Direction::LEFT ? "LEFT" : "RIGHT";
    m_result_str += ")";
}

void toString::visit(const rs::Flip &flp) {
    m_result_str = "Flip(";
    m_result_str += flp.axis() == rs::Flip::Axis::X ? "X" : "Y";
    m_result_str += ")";
}

void toString::visit(const rs::BlackNWhite &) {
    m_result_str = "B&W";
}
void toString::visit(const rs::Brightness &br) {
    m_result_str = "Brightness(" + rounded(std::to_string(br.percents())) + ")";
}

void toString::visit(const rs::Contrast &ct) {
    m_result_str = "Contrast(" + rounded(std::to_string(ct.percents())) + ")";
}
void toString::visit(const rs::Crop &cr) {

    m_result_str = "Crop(" +
                   rounded(std::to_string(cr.x()))
                    + "," +
                   rounded(std::to_string(cr.y()))
                    + "," +
                   rounded(std::to_string(cr.width()))
                    + "," +
                   rounded(std::to_string(cr.height()))
                    + ")";
}
} // ns rs
