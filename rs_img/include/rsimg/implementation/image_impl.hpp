#ifndef RS_IMAGE_IMPL_H
#define RS_IMAGE_IMPL_H

#include "../image.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

Image::ImageImpl& get_impl(Image &);

struct Image::ImageImpl {
    cv::Mat m_image;
    ImageImpl(std::string &&image_path);
    void write(std::string image_path);
};

} // namespace rs

#endif // RS_IMAGE_IMPL_H
