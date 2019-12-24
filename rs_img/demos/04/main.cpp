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

    auto strVisitor = rs::visitor::toString(t);
    
    std::cout << strVisitor.isVisited() << '\n' << strVisitor.result() << '\n';

    std::string str = rs::visitor::toString(rs::Crop(0, 0, 200, 200));
    std::cout << str << '\n';

    return 0;
}
