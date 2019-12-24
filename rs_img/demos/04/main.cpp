#include <iostream>
#include "../../include/rsimg/image.hpp"
#include "../../include/rsimg/transform.hpp"
#include "../../include/rsimg/visitor/to_string.hpp"
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

    rs::Composition t = rs::Rotate(rs::Rotate::Direction::LEFT)
                      * rs::BlackNWhite()
                      * rs::Contrast(30)
                      * rs::BlackNWhite();

    std::cout << rs::visitor::toString()(t) << '\n';

    rs::visitor::toString toStr;
    std::cout << toStr(t) << '\n';

    std::string str = toStr(rs::Crop(0, 0, 200, 200));
    std::cout << str << '\n';

    return 0;
}
