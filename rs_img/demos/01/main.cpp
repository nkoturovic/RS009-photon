#include <iostream>
#include "../../include/rsimg/image.hpp"
#include "../../include/rsimg/transform.hpp"
#include "../../include/rsimg/display.hpp"
#include "../../include/rsimg/exception.hpp"
#include "../../include/rsimg/implementation/image_impl.hpp"

int main()
{
    try 
    {
        rs::Image img1("lena.png"); // may throw

        img1 <<= rs::Rotate(rs::Rotate::Direction::LEFT) 
               * rs::Rotate(rs::Rotate::Direction::RIGHT);
        
        rs::Image img2 = img1 << rs::Rotate(rs::Rotate::Direction::LEFT) 
                               * rs::Flip(rs::Flip::Axis::Y)
                               * rs::BlackNWhite();

        rs::stdisp.show(img2);
        rs::Display::waitKey();

        img2.write("output.png");

    } catch (const rs::Exception &e) 
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
