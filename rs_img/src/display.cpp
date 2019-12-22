#include "../include/rsimg/display.hpp"
#include "../include/rsimg/exception.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"

namespace rs {

Display stdisp("Standard Image Display");

Display::Display(std::string name_of_display) : m_display_name(std::move(name_of_display)) {
    static unsigned displayCounter = 0;
    m_display_id = displayCounter++;
}

void Display::show(const Image &img) {
    try {
        cv::imshow(std::to_string(m_display_id) + ":" + m_display_name, get_impl(img).m_image);
    } catch (const cv::Exception &e) {
        throw rs::Exception("Error displaying image");
    }
}

void Display::waitKey(int delay) {
    cv::waitKey(delay);
}

}
