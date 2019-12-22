#include <iostream>
#include "../../include/rsimg/image.hpp"
#include "../../include/rsimg/transform.hpp"
#include "../../include/rsimg/display.hpp"
#include "../../include/rsimg/exception.hpp"

int main()
{
    rs::Image img1;

    try {
        img1 = rs::Image("lena.png"); // may throw
    } catch (const rs::Exception &e) 
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    img1 <<= rs::Contrast(100)
          * rs::Brightness(-50);

    auto img2 = img1;
    img1 <<= rs::Rotate(rs::Rotate::Direction::RIGHT);

    try {
        rs::stdisp.show(img1);
        rs::Display::waitKey();

        rs::stdisp.show(img2);
        rs::Display::waitKey();


    } catch (const rs::Exception& e) {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    return 0;
}
