#include <iostream>
#include "../undo.hpp"

int add3(int &x) { return x+=3; }

int main()
{
    rs::Undo<int> intUndo(2);
    const int &ref = intUndo.current();
    std::cout << ref << '\n'; 

    auto [succ0, nextSucc0] = intUndo.undo();
    std::cout << "[" << succ0 << "," << nextSucc0 << "] <- " << ref << '\n'; 
    std::cout << ref << '\n'; 

    intUndo.action(add3);
    intUndo.action([](int &x) { return x++; });
    std::cout << ref << '\n'; 

    auto [succ1, nextSucc1] = intUndo.redo();
    std::cout << "[" << succ1 << "," << nextSucc1 << "] <- " << ref << '\n'; 

    auto [succ2, nextSucc2] = intUndo.undo();
    std::cout << "[" << succ2 << "," << nextSucc2 << "] <- " << ref << '\n'; 

    auto [succ3, nextSucc3] = intUndo.redo();
    std::cout << "[" << succ3 << "," << nextSucc3 << "] <- " << ref << '\n'; 

    auto [succ4, nextSucc4] = intUndo.undo();
    std::cout << "[" << succ4 << "," << nextSucc4 << "] <- " << ref << '\n'; 

    intUndo.action([](int &x) {x = 333; });
    std::cout << ref << '\n'; 

    intUndo.action([](int &x) {x = 444; });
    std::cout << ref << '\n'; 

    auto [succ5, nextSucc5] = intUndo.redo();
    std::cout << "[" << succ5 << "," << nextSucc5 << "] <- " << ref << '\n'; 

    intUndo.action([](int &x) {x = 222; });
    std::cout << ref << '\n'; 

    for (bool has_more = true; has_more;) {
        auto [succ6, nextSucc6] = intUndo.undo();
        std::cout << "[" << succ6 << "," << nextSucc6 << "] <- " << ref << '\n'; 
        has_more = nextSucc6;
    }

    std::cout << ref << '\n'; 

    for (bool has_more = true; has_more;) {
        auto [succ6, nextSucc6] = intUndo.redo();
        std::cout << "[" << succ6 << "," << nextSucc6 << "] <- " << ref << '\n'; 
        has_more = nextSucc6;
    }

    intUndo.undo();

    int x = 10;
    std::cout << x << '\n';
    for (const auto &f : intUndo.previousActions()) {
        f->operator()(x);
        std::cout << x << '\n';
    }

    for (const auto &f : intUndo.nextActions()) {
        f->operator()(x);
        std::cout << x << '\n';
    }

    return 0;
}
