#include <iostream>

#include "undo.hpp"
#include "../rs_img/include/rsimg/display.hpp"
#include "../rs_img/include/rsimg/image.hpp"
#include "../rs_img/include/rsimg/exception.hpp"
#include "../rs_img/include/rsimg/transform.hpp"

int main()
{
    rs::Image img;

    try {
        img = rs::Image("lena.png");
    } catch (const rs::Exception &e) {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    rs::Undo<rs::Image> imgUndo = rs::Undo<rs::Image>(std::move(img));
    const rs::Image &imgRef = imgUndo.current();

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    imgUndo.action([](rs::Image &img) {
            img <<= rs::Rotate(rs::Rotate::Direction::RIGHT)
                  * rs::Rotate(rs::Rotate::Direction::RIGHT);
    });

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    imgUndo.action([](rs::Image &img) {
            img <<= rs::Flip(rs::Flip::Axis::Y);
    });

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ, succNextUndo] = imgUndo.undo();
    std::cout << succ << ' ' << succNextUndo << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ1, succNextUndo1] = imgUndo.undo();
    std::cout << succ1 << ' ' << succNextUndo1 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    return 0;
}
