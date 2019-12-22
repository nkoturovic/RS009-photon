#ifndef RS_DISPLAY_H
#define RS_DISPLAY_H

#include "image.hpp"

namespace rs {

class Display {
public:
    Display(std::string name_of_display = "Image Display");

    void show(const Image &img);
    static void waitKey(int delay=0);
private:
    unsigned m_display_id;
    std::string m_display_name;
};

extern Display stdisp;


} // namespace rs

#endif // RS_DISPLAY_H
