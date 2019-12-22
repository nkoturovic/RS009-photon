#ifndef RS_IMAGE_IMPL_H
#define RS_IMAGE_IMPL_H

#include "../image.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

Image::ImageImpl& get_impl(Image &);
const Image::ImageImpl& get_impl(const Image &);

struct Image::ImageImpl {
    cv::Mat m_image;
    ImageImpl();
    ImageImpl(std::string &&image_path);
    void write(std::string image_path);

    ImageImpl(const ImageImpl&);
    ImageImpl(ImageImpl &&);
    
    ImageImpl& operator=(const ImageImpl &);
    ImageImpl& operator=(ImageImpl &&);

    void swap(ImageImpl &);
};

} // namespace rs

#endif // RS_IMAGE_IMPL_H
