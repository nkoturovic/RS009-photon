#ifndef TO_STRING_VISITOR_H
#define TO_STRING_VISITOR_H

#include "../transform.hpp"
#include "../3rd_party/visitor_pattern.hpp"

namespace rs::visitor {
class ToString : public ConstTransformVisitorWithResult<std::string> {
    void visit(const Composition&) override;
    void visit(const Rotate&) override;
    void visit(const Flip&) override;
    void visit(const BlackNWhite&) override;
    void visit(const Brightness&) override;
    void visit(const Contrast&) override;
    void visit(const Crop&) override;
    void otherwise(const Transform&) override;
};

} // ns rs

#endif
