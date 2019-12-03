#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

namespace rs {

Image::ImageImpl& get_impl(Image &img) {
    return img.impl();
}

Image::ImageImpl::ImageImpl(std::string &&image_path) {
    /* Ukoliko slika nije uspesno ucitana, baciti exception */
    m_image = cv::imread( image_path, cv::IMREAD_COLOR );
    if( !m_image.data ){
        throw rs::Exception("Error reading image: " + image_path);
    }
}

void Image::ImageImpl::ImageImpl::write(std::string image_path) {
    cv::imwrite( image_path, m_image );
}

} // namespace rs
