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

    rs::Composition t1 = rs::Rotate(rs::Rotate::Direction::LEFT)
                       | rs::Contrast(30)
                       | rs::Flip(rs::Flip::Axis::Y)
                       | rs::BlackNWhite();

    rs::stdisp.show(img1 << t1);
    rs::Display::waitKey();

    /***** t2 is same as t1 *****/
    rs::Composition t2 = rs::BlackNWhite()
                       * rs::Flip(rs::Flip::Axis::Y)
                       * rs::Contrast(30)
                       * rs::Rotate(rs::Rotate::Direction::LEFT);
   
    rs::stdisp.show(img1 << t2);
    rs::Display::waitKey();

    std::cout << "T1 " << rs::visitor::ToString()(t1) << '\n';
    std::cout << "T2 " << rs::visitor::ToString()(t2) << '\n';

    const rs::Transform& tr = t1;

    rs::visitor::ToString toStr;
    std::cout << toStr(tr) << '\n';

    std::string str = toStr(tr);
    std::cout << str << '\n';

    /* Custom Visitor */
    struct MyVisitor : rs::ConstTransformVisitorWithResult<int> {
        void visit(const rs::Composition &arg) { result(1); }
        void visit(const rs::Rotate      &arg) { result(2); }
        void visit(const rs::Flip        &arg) { result(3); }
        void visit(const rs::BlackNWhite &arg) { result(4); }
        void otherwise(const rs::Transform &arg) { result(0); }
    };
    std::cout << MyVisitor()(tr) << '\n';

    return 0;
}
