#include "../include/rsimg/image.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"

namespace rs {

Image::Image() : m_pimpl{new ImageImpl()} {}
Image::Image(std::string image_path) : m_pimpl{new ImageImpl(std::move(image_path))} {}
Image::~Image() = default;

Image::ImageImpl& Image::impl() {
    return *m_pimpl;
}

const Image::ImageImpl& Image::impl() const {
    return *m_pimpl;
}

void Image::write(std::string image_path) { 
    this->impl().write(std::move(image_path));
}

size_t Image::width() const {return this->impl().width();}
size_t Image::height() const {return this->impl().height();}
size_t Image::step() const {return this->impl().step();}
const unsigned char * Image::data() {return this->impl().data();}


} // namespace rs
