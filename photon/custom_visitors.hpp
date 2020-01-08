#ifndef CUSTOM_VISITORS_HPP
#define CUSTOM_VISITORS_HPP

#include "rsimg/transform.hpp"
#include "undoitem.h"


struct ToStringSR : public rs::ConstTransformVisitorWithResult<std::string> {
    virtual ~ToStringSR() = default;
private:
    void visit(const rs::Composition&) override;
    void visit(const rs::Rotate&) override;
    void visit(const rs::Flip&) override;
    void visit(const rs::BlackNWhite&) override;
    void visit(const rs::Brightness&) override;
    void visit(const rs::Contrast&) override;
    void visit(const rs::Crop&) override;
    void visit(const rs::Invert &) override;
    void otherwise(const rs::Transform&) override;
};


struct UndoItemGenerator : public rs::ConstTransformVisitorWithResult<UndoItem*> {
    UndoItemGenerator(QWidget * parent) : m_parentPtr(parent) {}
    virtual ~UndoItemGenerator() = default;
private:
    QWidget * m_parentPtr = nullptr;
    void visit(const rs::Composition &) override;
    void visit(const rs::Rotate &) override;
    void visit(const rs::Flip &) override;
    void visit(const rs::BlackNWhite &) override;
    void visit(const rs::Brightness &) override;
    void visit(const rs::Contrast &) override;
    void visit(const rs::Crop &) override;
    void visit(const rs::Invert &) override;
    void otherwise(const rs::Transform &) override;
};

#endif // CUSTOM_VISITORS_HPP
