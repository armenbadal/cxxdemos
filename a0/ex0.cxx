
#include <iostream>

#include "list.hxx"


demo::list<int> f()
{
  demo::list<int> e0{10, 11, 12, 13};
  return e0;
}

int main()
{
  using namespace std;
  
  demo::list<char> a0;
  cout << a0.to_string() << endl;
  
  demo::list<int> a1{1, 2, 3, 4};
  cout << a1.to_string() << endl;

  auto k = a1.remove_from_end();
  cout << k << endl;
  cout << a1.to_string() << endl;

  demo::list<int> a2 = a1;
  cout << a2.to_string() << endl;

  demo::list<int> a3;
  a3 = f();
  cout << a3.to_string() << endl;
  

  
  return 0;
}

