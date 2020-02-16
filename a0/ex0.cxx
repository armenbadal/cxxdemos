
#include <iostream>

#include "list.hxx"


demo::list<int> f()
{
  demo::list<int> e0{10, 11, 12, 13};
  return e0;
}

void p(demo::list<int> l)
{
  std::cout << l.to_string() << std::endl;
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

  for(int e : a3)
    cout << e << endl;

  for(auto ai = a3.begin(); ai != a3.end(); ++ai)
    cout << (*ai) << endl;
  
  demo::list<int> a4{a3};
  p(std::move(a4));

  return 0;
}

