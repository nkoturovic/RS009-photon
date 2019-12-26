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

    const rs::Transform& tr = t;

    std::cout << rs::visitor::ToString()(tr) << '\n';

    rs::visitor::ToString toStr;
    std::cout << toStr(tr) << '\n';

    std::string str = toStr(tr);
    std::cout << str << '\n';

    /* struct/class syntax */
    struct myVisitor : rs::TransformVisitor<int> {
        void visit(const rs::Composition &arg) { result(1); }
        void visit(const rs::Rotate      &arg) { result(2); }
        void visit(const rs::Flip        &arg) { result(3); }
        void visit(const rs::BlackNWhite &arg) { result(4); }
        void visit(const rs::Brightness  &arg) { result(5); }
        void visit(const rs::Contrast    &arg) { result(6); }
        void visit(const rs::Crop        &arg) { result(7); }
        void visit(const rs::Transform   &arg) { result(8); }
    };
    std::cout << myVisitor()(tr) << '\n';

    /* lambda syntax */
    auto vis1 = rs::makeVisitor( 
        [](const rs::Composition &arg) { return "Composition"; },
        [](const rs::Rotate      &arg) { return "Rotation"; } ,
        [](const rs::Flip        &arg) { return "Flip"; }, 
        [](const rs::BlackNWhite &arg) { return "BlackNWhite"; }, 
        [](const auto &arg) /* otherwise */ { return "Other"; }
    );
    std::cout << vis1(tr) << '\n';

    rs::Contrast contrast = rs::Contrast(25.5);
    const rs::Transform &ref = contrast;

    auto vis2 = rs::makeVisitor( 
        [](const rs::Contrast    &arg) { return arg.percents(); }, 
        [](const rs::Composition &arg) { return 1.32; },
        [](const rs::Rotate      &arg) { return 2.32; } ,
        [](const rs::Flip        &arg) { return 3.32; }, 
        [](const rs::BlackNWhite &arg) { return 4.32; }, 
        [](const auto &arg)/* otherwise */ { return 5.32; }
    );
    std::cout << vis2(ref) << '\n';
    std::cout << vis2.result() << '\n';

    return 0;
}
