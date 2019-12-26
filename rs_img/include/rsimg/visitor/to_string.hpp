#ifndef TO_STRING_VISITOR_H
#define TO_STRING_VISITOR_H

#include "../transform.hpp"

namespace rs::visitor {

class ToString : public TransformVisitor<std::string> {
    RS_DECLARE_VISITORS
};

} // ns rs

#endif
