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

} // namespace rs
