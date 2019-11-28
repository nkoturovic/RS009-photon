#include "../include/rsimg/display.hpp"
#include "../include/rsimg/implementation/image_impl.hpp"

namespace rs {

Display stdisp("Standard Image Display");

Display::Display(std::string name_of_display) : m_display_name(std::move(name_of_display)) {
    static unsigned displayCounter = 0;
    m_display_id = displayCounter++;
}

void Display::show(Image &img) {
    /* TODO: @Andrijana (Napisati implementaciju) */
    /* Na raspolaganju: m_display_id, m_display_name i get_impl(img).m_image);  */
}

void Display::waitKey(int delay) {
    /* TODO: @Andrijana (Napisati implementaciju) */
}

}
