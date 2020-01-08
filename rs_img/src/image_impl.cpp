#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

namespace rs {

Image::ImageImpl& get_impl(Image &img) {
    return img.impl();
}

const Image::ImageImpl& get_impl(const Image &img) {
    return img.impl();
}

Image::ImageImpl::ImageImpl() : m_image(cv::Mat()) {}

Image::ImageImpl::ImageImpl(std::string &&image_path) {
    /* Ukoliko slika nije uspesno ucitana, baciti exception */
    m_image = cv::imread( image_path, cv::IMREAD_COLOR );
    if( !m_image.data ){
        throw rs::Exception("Error reading image: " + image_path);
     }
}

Image::ImageImpl::ImageImpl(const ImageImpl& other) : m_image(other.m_image.clone()) {
}

Image::ImageImpl::ImageImpl(ImageImpl &&other) {
    this->swap(other);
}

Image::ImageImpl& Image::ImageImpl::operator=(const ImageImpl &other) {
    ImageImpl tmp(other);
    this->swap(tmp);
    return *this;
}

Image::ImageImpl& Image::ImageImpl::operator=(ImageImpl &&other) {
    ImageImpl tmp(std::move(other));
    this->swap(tmp);
    return *this;
}

void Image::ImageImpl::swap(Image::ImageImpl &other) {
    std::swap(m_image, other.m_image);
}

void Image::ImageImpl::ImageImpl::write(std::string image_path) const {
    cv::imwrite(image_path, m_image);
}

size_t Image::ImageImpl::width() const {
    return this->m_image.cols;
}

size_t Image::ImageImpl::height() const {
    return this->m_image.rows;
}

size_t Image::ImageImpl::step() const {
    return this->m_image.step;
}

const unsigned char * Image::ImageImpl::data() const {
    return this->m_image.data;
}


} // namespace rs
