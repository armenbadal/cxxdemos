
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

#include "shared.hxx"
#include "unique.hxx"

// example class
struct A {
    A()
    {
        std::cout << "A()\n";
    }
    ~A()
    {
        std::cout << "~A()\n";
    }
};
A* create_A()
{
    std::cout << "create_A()\n";
    return new A;
}
void destroy_A(A* p)
{
    std::cout << "destroy_A()\n";
    delete p;
}
struct _ds {
    void operator()(A* p)
    {
        delete p;
    }
};

int main()
{
    using namespace std;

    //unique_ptr<A, decltype(&destroy_A)> up0(create_A(), destroy_A);

    //auto _d = [](A* p) { delete p; };
    //unique_ptr<A, decltype(_d)> up1(create_A(), _d);

    //unique_ptr<A, _ds> up2(create_A(), _ds());


    //shared::pointer<A, decltype(&destroy_A)> p0(create_A(), destroy_A);

    //auto _d = [](A* p) { delete p; };
    //shared::pointer<A, decltype(_d)> p1(create_A(), _d);

    //shared::pointer<A, _ds> p2(create_A(), _ds());

    //shared::pointer p3(new A);

    unique::pointer<A> q0;

    return 0;
}
