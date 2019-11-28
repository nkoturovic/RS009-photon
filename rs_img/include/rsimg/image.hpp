#ifndef RS_IMAGE_H
#define RS_IMAGE_H

#include <string>
#include "3rd_party/spimpl.h"

namespace rs {

class Image {
private:
    struct ImageImpl;
    friend ImageImpl& get_impl(Image &);

    spimpl::impl_ptr<ImageImpl> m_pimpl; 
    ImageImpl& impl();

public:
    Image(std::string image_path);
    ~Image();

    void write(std::string image_path);
};

}

#endif // RS_IMAGE_H
