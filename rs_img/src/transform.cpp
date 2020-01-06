#include "../include/rsimg/transform.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

namespace rs {

Rotate::Rotate(Rotate::Direction direction) : m_direction(direction) {}

Image& Rotate::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    switch (m_direction) {
        case Direction::RIGHT : cv::rotate( imageRef, imageRef, cv::ROTATE_90_CLOCKWISE); break;
        case Direction::LEFT : cv::rotate( imageRef, imageRef, cv::ROTATE_90_COUNTERCLOCKWISE); break;
    }
    return img;
}

Flip::Flip(Axis axis) : m_axis(axis) {}

Image& Flip::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::flip(imageRef, imageRef, static_cast<int>(m_axis));
    return img;
}

BlackNWhite::BlackNWhite() { }

Image& BlackNWhite::applyImpl(Image &img) const { 
    cv::Mat &imageRef = get_impl(img).m_image;

    try {
        cv::cvtColor(imageRef, imageRef, cv::COLOR_BGR2GRAY );
    } catch (const cv::Exception &) {
        throw rs::Exception("Can not convert colors");
    }

    return img;
}

Brightness::Brightness(double percents) : m_percents(percents) {}

Image& Brightness::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    auto val = m_percents / 100 * 255;
    imageRef.convertTo(imageRef, -1, 1, val);

    return img;
}

Invert::Invert() { }

Image& Invert::applyImpl(Image &img) const { 
    cv::Mat &imageRef = get_impl(img).m_image;

    try {
        cv::bitwise_not(imageRef, imageRef);
    } catch (const cv::Exception &) {
        throw rs::Exception("Can not convert colors");
    }

    return img;
}

Contrast::Contrast(double percents) : m_percents(percents) {
}

Image& Contrast::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;

    auto val = (m_percents / 100) + 1;
    imageRef.convertTo(imageRef, -1, val, 0);
    return img;
}
Crop::Crop(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height)
    {}

Image& Crop::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    imageRef(cv::Rect(m_x, m_y, m_width, m_height)).copyTo(imageRef);
    return img;
}

} // namespace rs
