#include <iostream>
#include "undo.hpp"

int main()
{
    
    rs::Undo<int> intHist(2);
    std::cout << intHist.current() << '\n'; 

    auto [succ0, nextSucc0] = intHist.undo();
    std::cout << "[" << succ0 << "," << nextSucc0 << "] <- " << intHist.current() << '\n'; 


    intHist.action([](int &x) {x++;});
    std::cout << intHist.current() << '\n'; 

    auto [succ1, nextSucc1] = intHist.redo();
    std::cout << "[" << succ1 << "," << nextSucc1 << "] <- " << intHist.current() << '\n'; 

    auto [succ2, nextSucc2] = intHist.undo();
    std::cout << "[" << succ2 << "," << nextSucc2 << "] <- " << intHist.current() << '\n'; 

    auto [succ3, nextSucc3] = intHist.redo();
    std::cout << "[" << succ3 << "," << nextSucc3 << "] <- " << intHist.current() << '\n'; 

    //auto [succ4, nextSucc4] = intHist.undo();
    //std::cout << "[" << succ4 << "," << nextSucc4 << "] <- " << intHist.current() << '\n'; 

    intHist.action([](int &x) {x = 333; });
    std::cout << intHist.current() << '\n'; 

    intHist.action([](int &x) {x = 444; });
    std::cout << intHist.current() << '\n'; 

    auto [succ5, nextSucc5] = intHist.redo();
    std::cout << "[" << succ5 << "," << nextSucc5 << "] <- " << intHist.current() << '\n'; 

    intHist.action([](int &x) {x = 222; });
    std::cout << intHist.current() << '\n'; 

    for (bool has_more = true; has_more;) {
        auto [succ6, nextSucc6] = intHist.undo();
        std::cout << "[" << succ6 << "," << nextSucc6 << "] <- " << intHist.current() << '\n'; 
        has_more = nextSucc6;
    }

    std::cout << intHist.current() << '\n'; 

     for (bool has_more = true; has_more;) {
         auto [succ6, nextSucc6] = intHist.redo();
         std::cout << "[" << succ6 << "," << nextSucc6 << "] <- " << intHist.current() << '\n'; 
         has_more = nextSucc6;
     }


    return 0;
}
