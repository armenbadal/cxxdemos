
#ifndef _LIST_CXX_
#define _LIST_CXX_

#include <exception>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace {
  void __p(const char* m)
  {
    std::cout << "INFO: " << m << std::endl;
  }
}

namespace demo {

struct empty_list_error : public std::logic_error {
  using std::logic_error::logic_error;
};
  
template<typename E>
class list {
public:
  struct node {
    E data;
    node* next;

    node(const E& d, node* n)
      : data{d}, next{n}
    {}
  };

public:
  using value_type = E;
  
  list() = default;
  
  list(std::initializer_list<E> els)
  {
    //__p("list(std::initializer_list<E> els)");
    for( auto& e : els )
      add_to_end(e);
  }
  
  list(const list& l)
  {
    //__p("list(const list& l)");
    _destroy_all(_head);
    for( auto _p = l._head; _p != nullptr; _p = _p->next )
      add_to_end(_p->data);
  }
  
  list(list&& l)
    : _head{l._head}, _count{l._count}
  {
    //__p("list(list&& l)");
    l._head = nullptr;
    l._count = 0;
  }
  
  ~list()
  {
    _destroy_all(_head);
    _head = nullptr;
  }
  
  list& operator=(const list& l)
  {
    //__p("list& operator=(const list& l)");
    if( this != &l ) {
      _destroy_all(_head);
      for( auto _p = l._head; _p != nullptr; _p = _p->next )
	add_to_end(_p->data);
    }
    return *this;
  }
  
  list& operator=(list&& l)
  {
    //__p("list& operator=(list&& l)");
    if( this != &l ) {
      _head = std::exchange(l._head, _head);
      _count = std::exchange(l._count, _count);
    }
    return *this;
  }

  bool is_empty() const
  {
    return 0 == _count;
  }

  size_t count() const
  {
    return _count;
  }
  
  list& add_to_front(const E& d)
  {
    _head = new node(d, _head);
    ++_count;
    return *this;
  }

  E remove_from_front()
  {
    if( is_empty() )
      throw empty_list_error{""};
    
    auto _p = _head;
    _head = _head->next;
    --_count;
    auto _v = _p->data;
    delete _p;
    return _v;
  }
  
  list& add_to_end(const E& d)
  {
    _head = _add_after(d, _head);
    ++_count;
    return *this;
  }

  E remove_from_end()
  {
    if( is_empty() )
      throw empty_list_error{""};

    if( 1 == count() ) {
      auto _v = _head->data;
      delete _head;
      --_count;
      return _v;
    }

    auto _p = _head;
    while( _p->next->next != nullptr )
      _p = _p->next;
    auto _v = _p->next->data;
    delete _p->next;
    --_count;
    _p->next = nullptr;
    return _v;
  }

  std::string to_string()
  {
    std::stringstream s;
    s << "L[" << _count << "] = { ";
    auto p = _head;
    while( p != nullptr ) {
      s << p->data << ' ';
      p = p->next;
    }
    s << '}';
    return s.str();
  }

private:
  node* _add_after(const E& d, node* r)
  {
    if( nullptr == r )
      return new node(d, nullptr);

    r->next = _add_after(d, r->next);
    return r;
  }

  void _destroy_all(node* r)
  {
    if( r != nullptr ) {
      _destroy_all(r->next);
      delete r;
    }
    _count = 0;
  }
  
private:
  node* _head = nullptr;
  size_t _count = 0;

public:
  class iterator {
  public:
    iterator() = default;
    
    explicit iterator(const list<E>& l)
      : _it{l._head}
    {}

    bool operator!=(const iterator& i)
    {
      return _it != i._it;
    }

    iterator& operator++()
    {
      _it = _it->next;
      return *this;
    }

    E operator*()
    {
      return _it->data;
    }
    
  private:
    node* _it = nullptr;
  };

  iterator begin()
  {
    return iterator{*this};
  }

  iterator end()
  {
    return {};
  }
};

template<typename E>
decltype(auto) begin(const list<E>& l)
{
  return l.begin();
}

template<typename E>
decltype(auto) end(const list<E>& l)
{
  return l.end();
}
} // namespace demo


#endif //_LIST_CXX_


