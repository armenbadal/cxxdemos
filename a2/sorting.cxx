
#include <algorithm>
#include <array>
#include <iostream>
#include <ostream>

namespace sort {
    template<typename E, size_t N>
    void selection(std::array<E,N>& arr)
    {
        for( auto i = arr.begin(); i < arr.end() - 1; ++i )
            if( auto me = std::min_element(i, arr.end()); i != me )
                std::iter_swap(i, me);
    }

    template<typename E, size_t N>
    void insertion(std::array<E,N>& arr)
    {
        for( size_t i = 1; i < arr.size(); ++i )
            for( size_t j = i; j > 0 && arr[j] < arr[j-1]; --j )
                std::swap(arr[j], arr[j-1]);
    }

    void merge()
    {}
}

template<typename E, size_t N>
std::ostream& operator<<(std::ostream& ooo, const std::array<E,N>& arr)
{
    for( auto& e : arr )
        ooo << e << ' ';
    return ooo;
}


int main()
{
    std::array<int, 10> a0{6, 1, 0, 5, 7, 2, 9, 3, 4, 8};
    std::cout << a0 << std::endl;
    sort::insertion(a0);
    std::cout << a0 << std::endl;
}
