#include <iostream>
#include "../../include/rsimg/image.hpp"
#include "../../include/rsimg/transform.hpp"
#include "../../include/rsimg/display.hpp"
#include "../../include/rsimg/exception.hpp"

int main()
{
    try 
    {
        rs::Image img("lena.png"); // may throw
        img <<= rs::Contrast(100)
              * rs::Brightness(-50);
        rs::stdisp.show(img);
        rs::Display::waitKey();

    } catch (const rs::Exception &e) 
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
