
#ifndef _BTREE_HXX_
#define _BTREE_HXX_

#include <stack>

namespace demo {

template<typename Y>
class binary_tree {
public:
    struct node {
        Y data;
        node* left = nullptr;
        node* right = nullptr;

        node(const Y& v, node* l, node* r)
            : data{v}, left{l}, right{r}
        {}

        node(const Y& v)
            : data{v}
        {}
    };

public:
    binary_tree() = default;

    void add(const Y& v)
    {
        _root = _add(v, _root);
    }

private:
    node* _add(const Y& v, node* r)
    {
        if( nullptr == r )
            return new node(v);

        if( v < r->data )
            r->left = _add(v, r->left);
        else if( v > r->data ) 
            r->right = _add(v, r->right);

        return r;
    }

private:
    node* _root = nullptr;

public:
    class iterator {
    public:
        iterator() = default;
        iterator(const binary_tree<Y>& t)
        {
            if( t._root != nullptr ) {
                _ni = t._root;
                _s.push(_ni->right);
                _s.push(_ni->left);
            }
        }

        bool operator!=(const iterator _i)
        {
            return _ni != _i._ni;
        }

        Y operator*()
        {
            return _ni->data;
        }

        iterator& operator++()
        {
            if( _s.empty() )
                _ni = nullptr;
            else {
                _ni = _s.top(); _s.pop();
                if( _ni->right != nullptr )
                    _s.push(_ni->right);
                if( _ni->left != nullptr )
                    _s.push(_ni->left);
            }
            return *this;
        }

    private:
        node* _ni = nullptr;
        std::stack<node*> _s;
    };

    iterator begin()
    {
        return iterator{*this};
    }

    iterator end()
    {
        return iterator{};
    }
};
} // namespace demo

#endif //_BTREE_HXX_
