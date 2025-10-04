#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void)
{
    int r = rand() % 3;
    switch (r)
    {
        case 0:
            std::cout << "Generated: A\n";
            return new A;
        case 1:
            std::cout << "Generated: B\n";
            return new B;
        default:
            std::cout << "Generated: C\n";
            return new C;
    }
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "identify(*): A\n";
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "identify(*): B\n";
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "identify(*): C\n";
    else
        std::cout << "identify(*): Unknown\n";
}

// -- Using nested try/catch with catch(...) to avoid <typeinfo> --
void identify(Base& p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        (void)a; // silence unused var warning
        std::cout << "identify(&): A\n";
        return;
    }
    catch (...)
    {
        // Not A
    }
    try
    {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "identify(&): B\n";
        return;
    }
    catch (...)
    {
        // Not B
    }
    try
    {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "identify(&): C\n";
        return;
    }
    catch (...)
    {
        // Not C
    }
    std::cout << "identify(&): Unknown\n";
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Base* basePtr = generate();
    identify(basePtr);
    identify(*basePtr);

    delete basePtr;
    return 0;
}
