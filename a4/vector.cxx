
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

namespace demo {
    template<typename Y>
    class vector {
    public:
        vector()
            : vector(16)
        {}

        explicit vector(std::size_t cp)
            : _capacity{cp},
            _count{0},
            _elements{std::make_unique<Y[]>(_capacity)}
        {}

        vector(std::initializer_list<Y> els)
            : vector(els.size())
        {
            std::copy(els.begin(), els.end(), _elements.get());
            _count = els.size();
        }

        vector(const vector& other)
            : vector(other.size())
        {
            const auto p0 = other._elements.get();
            std::copy(p0, p0 + other._count, _elements.get());  
            _count = other._count;          
        }

        vector(vector&& other)
        {
            // TODO
        }

        ~vector()
        {
            _elements = nullptr;
        }

        vector& operator=(const vector& other)
        {
            if( &other != this ) {
                // TODO
            }

            return *this;
        }

        vector& operator=(vector&& other)
        {
            if( &other != this ) {
                // TODO
            }
            return *this;
        }

        std::size_t size() const
        {
            return _count;
        }

        // void push_front(const Y& v)
        // {
        //     if( _count == _capacity )
        //         resize(_capacity * 2);

        //     for( std::size_t i = _count; i > 0; --i )
        //         _elements[i] = std::move(_elements[i-1]);

        //     _elements[0] = v;
        //     ++_count;
        // }

        void push_back(const Y& v)
        {
            if( _count == _capacity )
                resize(_capacity * 2);

            _elements[_count] = v;
            ++_count;
        }

        void pop_back()
        {
            if( 0 != _count )
                --_count;
        }

        Y& operator[](std::size_t ix)
        {
            return _elements[ix];
        }

        const Y& operator[](std::size_t ix) const
        {
            return _elements[ix];
        }

        /* DEBUG */
        void print()
        {
            std::cout << "C: " << _capacity << std::endl;
            std::cout << "S: " << _count << std::endl;
            for( std::size_t i = 0; i < _count; ++i )
                std::cout << i << ':' << _elements[i] << std::endl;
        }

    private:
        void resize(std::size_t sz)
        {
            _capacity = sz;
            auto _els = std::make_unique<Y[]>(_capacity);
            const auto p0 = _elements.get();
            std::copy(p0, p0 + _count, _els.get());
            _elements = std::move(_els);
        }

    private:
        std::size_t _capacity{0};
        std::size_t _count{0};
        std::unique_ptr<Y[]> _elements{nullptr};
    };
} // demo


int main()
{
    demo::vector<int> v0(4);
    v0.push_back(1);
    v0.push_back(2);
    v0.push_back(3);
    v0.push_back(4);
    v0.push_back(5);
    v0.push_back(6);
    // v0.push_front(99);
    v0.print();

    return 0;
}
