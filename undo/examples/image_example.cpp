#include <iostream>

#include "../undo.hpp"
#include "../../rs_img/include/rsimg/display.hpp"
#include "../../rs_img/include/rsimg/image.hpp"
#include "../../rs_img/include/rsimg/exception.hpp"
#include "../../rs_img/include/rsimg/transform.hpp"
#include "../../rs_img/include/rsimg/visitor/to_string.hpp"

int main()
{
    rs::Image img;

    try {
        img = rs::Image("lena.png");
    } catch (const rs::Exception &e) {
        std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    auto imgUndo = rs::Undo<rs::Image, rs::Transform>(std::move(img));
    const rs::Image &imgRef = imgUndo.current();

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    imgUndo.action(rs::Rotate(rs::Rotate::Direction::RIGHT) *
                   rs::Rotate(rs::Rotate::Direction::RIGHT));

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    imgUndo.action(rs::Flip(rs::Flip::Axis::Y) * rs::Brightness(50));

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    rs::visitor::ToString toStr;

    for (const auto &t : imgUndo.previousActions())
        std::cout << toStr(*t) << '\n'; 

    auto [succ, succNextUndo] = imgUndo.undo();
    std::cout << succ << ' ' << succNextUndo << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ1, succNextUndo1] = imgUndo.undo();
    std::cout << succ1 << ' ' << succNextUndo1 << '\n';

    imgUndo.action(rs::BlackNWhite());

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ2, succNextUndo2] = imgUndo.redo();
    std::cout << succ2 << ' ' << succNextUndo2 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ3, succNextUndo3] = imgUndo.undo();
    std::cout << succ3 << ' ' << succNextUndo3 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ4, succNextUndo4] = imgUndo.undo();
    std::cout << succ4 << ' ' << succNextUndo4 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ5, succNextUndo5] = imgUndo.redo();
    std::cout << succ5 << ' ' << succNextUndo5 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    auto [succ6, succNextUndo6] = imgUndo.redo();
    std::cout << succ6 << ' ' << succNextUndo6 << '\n';

    rs::stdisp.show(imgRef);
    rs::Display::waitKey();

    return 0;
}
