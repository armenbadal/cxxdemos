
#include <iostream>
#include <memory>


int main()
{
    using namespace std;

    auto u0 = make_unique<char[]>(8);
    u0[0] = 'a';
    u0[7] = 'g';
    auto q = u0.get();
    
    u0 = make_unique<char[]>(16);
    u0[0] = 'a';
    u0[7] = 'g';
    auto p = u0.get();

    cout << sizeof(u0) << endl;

    return 0;
}
