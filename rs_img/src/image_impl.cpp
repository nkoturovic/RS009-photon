#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

namespace rs {

Image::ImageImpl& get_impl(Image &img) {
    return img.impl();
}

Image::ImageImpl::ImageImpl(std::string &&image_path) {
    /* TODO: @Andrijana (Napisati implementaciju) */
    /* Ukoliko slika nije uspesno ucitana, baciti exception */
    throw rs::Exception("Error reading image: " + image_path);
}

void Image::ImageImpl::ImageImpl::write(std::string image_path) {
    /* TODO: @Andrijana (Napisati implementaciju) */
}

} // namespace rs
