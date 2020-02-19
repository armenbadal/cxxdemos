
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <stack>

template<typename Y>
class binary_search_tree {
public:
    struct node {
        Y data{};
        size_t count{0};
        std::shared_ptr<node> left{nullptr};
        std::shared_ptr<node> right{nullptr};

        node(const Y& d)
            : data{d}, count{1}
        {}
    };

    using node_sp = std::shared_ptr<node>;

public:
    using value_type = Y;

    binary_search_tree() = default;

    binary_search_tree(std::initializer_list<Y> els)
    {
        for( auto& e : els )
            add(e);
    }

    ~binary_search_tree()
    {
        _root = nullptr;
    }

    binary_search_tree& add(const Y& v)
    {
        _root = add(v, _root);
        return *this;
    }

    binary_search_tree& operator<<(const Y& v)
    {
        return add(v);
    }

private:
    decltype(auto) add(const Y& v, node_sp r)
    {
        if( r == nullptr )
            return std::make_shared<node>(v);

        if( v < r->data )
            r->left = add(v, r->left);
        else if( v > r->data )
            r->right = add(v, r->right);
        else
            r->count += 1;

        return r;
    }

private:
    node_sp _root{nullptr};

public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Y;
        using reference = value_type&;

        iterator() = default;

        iterator(const binary_search_tree<Y>& bt)
        {
            auto p = bt._root;
            while( p != nullptr ) {
                _stack.push(p);
                p = p->left;
            }

            ++(*this);
        }

        bool operator!=(const iterator& other)
        {
            return _bi != other._bi;
        }

        iterator& operator++()
        {
            if( _stack.empty() ) {
                _bi = nullptr;
                return *this;
            }

            _bi = _stack.top(); _stack.pop();
            auto p = _bi->right;
            while( p != nullptr ) {
                _stack.push(p);
                p = p->left;
            }

            return *this;
        }

        value_type operator*()
        {
            return _bi->data;
        }

    private:
        node_sp _bi{nullptr};
        std::stack<node_sp> _stack;
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



int main()
{
    using namespace std;

    binary_search_tree<int> b0{5, 2, 8, 11, 15, 6, 1, 4};

    for( int e : b0 )
        cout << e << ' ';
    cout << endl;

    binary_search_tree<int> b1;
    b1 << 5 << 4 << 10 << 2 << 8 << 12 << 1 << 3 << 7 << 9 << 11 << 13 << 6;

    for( int e : b1 )
        cout << e << ' ';
    cout << endl;

    for_each(b1.begin(), b1.end(), [&](auto e) { cout << e << '*'; });
    auto k = reduce(b1.begin(), b1.end(), 0);

    return 0;
}
