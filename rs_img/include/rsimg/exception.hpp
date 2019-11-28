#ifndef RS_EXCEPTION_H
#define RS_EXCEPTION_H

#include <stdexcept>
#include <sstream>

namespace rs {

class Exception : std::runtime_error {
public:
    Exception(const std::string &err_msg) : std::runtime_error("[RS] " + err_msg) { }

    virtual const char * what() const noexcept override {
        return std::runtime_error::what();
    }
};

} // namespace rs

#endif
