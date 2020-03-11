
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

    template<typename E, size_t N>
    void merge(std::array<E,N>& ar, size_t l, size_t h, std::array<E,N> ax)
    {
        if( h <= l )
            return;

        size_t m = l + (h - l) / 2;
        merge(ar, l, m, ax);
        merge(ar, m+1, h, ax);

        for( size_t k = l, i = l, j = m + 1; k <= h; ++k )
            if( i > m )
                ax[k] = ar[j++];
            else if( j > h )
                ax[k] = ar[i++];
            else if( ar[j] < ar[i] )
                ax[k] = ar[j++];
            else
                ax[k] = ar[i++];

        for( size_t k = l; k <= h; ++k )
            ar[k] = ax[k];
    }

    template<typename E, size_t N>
    void merge(std::array<E,N>& arr)
    {
        std::array<E,N> ax;
        merge(arr, 0, arr.size() - 1, ax);
    }

    template<typename E, size_t N>
    void quick(std::array<E,N>& arr)
    {        
    }
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
    sort::merge(a0);
    std::cout << a0 << std::endl;
}
