
#include <iostream>

#include "btree.hxx"




int main()
{   
    using namespace std;

    demo::binary_tree<int> b0;
    b0.add(5);
    b0.add(2);
    b0.add(8);
    b0.add(1);
    b0.add(12);
    b0.add(7);

    auto i = b0.begin();
    while( i != b0.end() ) {
        cout << (*i) << endl;
        ++i;
    }
}
