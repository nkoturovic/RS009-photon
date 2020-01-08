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
        cv::cvtColor(imageRef, imageRef, cv::COLOR_GRAY2BGR );
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

cv::Mat createLUT(int numColors) {
    cv::Mat lookupTable = cv::Mat::zeros(cv::Size(1, 256), CV_8UC1);
    int start = 0;

    for (int x = 0; x < 256; x += 256.0 / numColors) {
        lookupTable.at<unsigned char>(x, 0) = x;

        for (int y = start; y < x; y++) {
            if (lookupTable.at<unsigned char>(y, 0) == 0) {
                lookupTable.at<unsigned char>(y, 0) = lookupTable.at<unsigned char>(x, 0);
            }
        }
        start = x;
    }
    return lookupTable;
}

void reduceColors(cv::Mat img, int numRed, int numGreen, int numBlue) {
    std::vector<cv::Mat> BGR = std::vector<cv::Mat>(3);
    cv::split(img, BGR);

    if(numRed != 0){
        cv::Mat redLUT = createLUT(numRed);
        cv::LUT(BGR[2], redLUT, BGR[2]);
    } else {
        BGR[2] = 0;
    }
    
    if(numGreen != 0){
        cv::Mat greenLUT = createLUT(numGreen);
        cv::LUT(BGR[1], greenLUT, BGR[1]);        
    }else {
        BGR[1] = 0;
    }

    if(numBlue != 0){
        cv::Mat blueLUT = createLUT(numBlue);
        cv::LUT(BGR[0], blueLUT, BGR[0]);
    }else {
        BGR[0] = 0;
    }

    cv::merge(BGR, img);
}

void cartoon(cv::Mat &img, int numRed, int numGreen, int numBlue) {
    reduceColors(img, numRed, numGreen, numBlue);

    cv::Mat result = cv::Mat();
    cv::cvtColor(img, result, cv::COLOR_BGR2GRAY);
    cv::medianBlur(result, result, 15);

    cv::adaptiveThreshold(result, result, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, 2);

    cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);

    cv::bitwise_and(img, result, img);

}

Overlay::Overlay(Color color) : m_color(color) {}
Overlay::Color Overlay::color() const { return m_color; }

Image& Overlay::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    switch (m_color) {
        case Color::RED : reduceColors(imageRef, 50, 0, 0); break;
        case Color::GREEN : reduceColors(imageRef, 0, 50, 0); break;;
        case Color::BLUE : reduceColors(imageRef, 0, 0, 50); break;

    }
    return img;
}

Blur::Blur(int percent) : m_percent(percent) {}
int Blur::percent() const { return m_percent; }

Image& Blur::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    if(m_percent < 4){
        return img;
    }
    int val = m_percent / 4;
    auto ksize = cv::Size(val, val);
    cv::blur(imageRef, imageRef, ksize); 

    return img;
}

Image& Cartoon::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cartoon(imageRef, 80, 15, 10);
    return img;
}

Image& Neon::applyImpl(Image &img) const {
   cv::Mat &imageRef = get_impl(img).m_image;
   cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_COOL);
    return img;
}

Image& Winter::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_OCEAN);
    return img;
}

Image& Sepia::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_PINK);
    return img;
}

Image& Silver::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_BONE);
    return img;
}

Image& Rainbow::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_RAINBOW);
    return img;
}

Image& Summer::applyImpl(Image &img) const {
    cv::Mat &imageRef = get_impl(img).m_image;
    cv::applyColorMap(imageRef, imageRef, cv::COLORMAP_HOT);
    return img;
}

} // namespace rs
