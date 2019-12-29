#include <iostream>
#include "../../include/rsimg/image.hpp"
#include "../../include/rsimg/transform.hpp"
#include "../../include/rsimg/display.hpp"
#include "../../include/rsimg/exception.hpp"

int main()
{
    try {
        rs::Image img("lena.png");

        img <<= rs::Rotate(rs::Rotate::Direction::LEFT) 
              | rs::Rotate(rs::Rotate::Direction::RIGHT);
        
        rs::Image img2 = img << (rs::Rotate(rs::Rotate::Direction::LEFT) 
                              |  rs::Flip(rs::Flip::Axis::X)
                              |  rs::Crop(100, 100, 50, 50));

        rs::stdisp.show(img); // stdisp objekat
        rs::Display::waitKey();

        rs::Display disp1; // Neimenovan display
        img <<= rs::Flip(rs::Flip::Axis::Y) * rs::BlackNWhite();
        disp1.show(img);

        rs::Display disp2("Imenovan display");
        disp2.show(img2);

        rs::Display::waitKey();

        img.write("output1.png");
        img2.write("output2.png");

    } catch (const rs::Exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
