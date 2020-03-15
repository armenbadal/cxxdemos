#ifndef _SHARED_HXX_
#define _SHARED_HXX_

#include <cstddef>
#include <utility>

//
// Ընդհանուր ռեսուրս օգտագործող «խելացի» ցուցիչ։
// Նմանությամբ. https://en.cppreference.com/w/cpp/memory/shared_ptr
//
// Բնականաբար shared::pointer-ը լրիվ չէ և որոշ դեպքերի համար այն
// հնարավոր չի լինի օգտագործել։ Ես սա գրել եմ պարզապես ընդհանուր 
// սկզբունքների ցուցադրման նպատակով։
//
namespace shared {
    //
    template<typename Y>
    void _default_deleter(Y* p)
    {
        delete p;
    }

    //
    template<typename Y, typename D = decltype(_default_deleter<Y>)*>
    class pointer {
    public:
        // լռելյայն կոնստրուկտոր
        pointer() = default;

        // հասարակ ցուցիչով կոնստրուկտոր
        pointer(Y* p)
            : pointer(p, &_default_deleter)
        {}

        // հասարակ ցուցիչով և մաքրող գործողությամբ կոնստրուկտոր
        pointer(Y* p, D d)
            : _ptr{p},
            _deleter{d}
        {
            create_counter();
        }

        // զրոյական ցուցիչի համար
        pointer(std::nullptr_t)
        {}

        // պատճենող կոնստրուկտոր
        pointer(const pointer& other)
            : _ptr{other._ptr},
            _counter{other._counter}
        {
            // պատճենելիս մեկով ավելացնում ենք ընդհանուր հաշվիչը
            *_counter += 1;
        }

        // «յուրացնող» կոնստրուկտոր
        pointer(pointer&& other)
        {
            // յուրացնել ցուցիչը
            _ptr = std::exchange(other._ptr, nullptr);
            // յուրացնել հաշվիչը (այս դեպքում հաշվիչը չենք ավելացնում)
            _counter = std::exchange(other._counter, nullptr);
            // յուրացնել մաքրող գործողությունը
            _deleter = std::exchange(other._deleter, {});
        }

        // դեստրուկտոր
        ~pointer()
        {
            // հրաժարվել ռեսուրսից
            abandon();
        }

        // պատճենող վերագրում
        pointer& operator=(const pointer& other)
        {
            // հրաժարվել «հին» ռեսուրսից
            abandon();
            // հղվել «նոր» ռեսուրսին
            _ptr = other._ptr;
            _counter = other._counter;
            // մեկով ավելացնել հաշվիչը
            *_counter += 1;
            // հղվել (պատճենել ?) մաքրող գործողությունը
            _deleter = other._deleter;
        }

        // «յուրացնող» վերագրում
        pointer& operator=(pointer&& other)
        {
            // հրաժարվել «հին» ռեսուրսից
            abandon();
            // յուրացնել ցուցիչը
            _ptr = std::exchange(other._ptr, _ptr);
            // յուրացնել հաշվիչը (այս դեպքում հաշվիչը չենք ավելացնում)
            _counter = std::exchange(other._counter, _counter);
            // յուրացնել մաքրող գործողությունը
            _deleter = std::exchange(other._deleter, _deleter);
        }

        // զրոյացնող վերագրում
        pointer& operator=(std::nullptr_t)
        {
            // հրաժարվել «հին» ռեսուրսից
            abandon();
            _ptr = nullptr;
        }

        // ցուցիչի զրոյական լինելու ստուգում
        operator bool() const
        {
            return _ptr != nullptr;
        }

        Y* operator->() const
        {
            return _ptr;
        }

        Y& operator*() const
        {
            return *_ptr;
        }

        // հաշվիչի արժեքը
        auto counter() const
        {
            return *_counter;
        }

    private:
        // ռեսուրսից հրաժարվելու պրոցեդուրան
        void abandon()
        {
            // պակասեցնել հաշվիչը մեկով
            *_counter -= 1;
            // եթե հաշվիչ դարձավ զրո...
            if( 0 == *_counter ) {
                // ... ազատել ռեսուրսի հիշողությունը
                _deleter(_ptr);
                // ... և ազատել հաշվիչի հիշողությունը
                delete _counter;
            }
        }

        // ստեղծել հաշվիչը և տալ նախնական արժեք
        void create_counter()
        {
            // ստեղծել հաշվիչը
            _counter = new std::size_t;
            // վերագրել 1 արժեքը
            *_counter = 1;
        }

    private:
        Y* _ptr{nullptr}; // ցուցիչը
        std::size_t* _counter{nullptr}; // հաշվիչը
        D _deleter{}; // մաքրող գործողությունը
    };

    // TODO: սահմանել համեմատման գործողություններ

    // shared::pointer տիպի նոր օբյեկտներ սարքելու համար
    template<typename Y, typename... S>
    pointer<Y> create(S... as)
    {
        return pointer<Y>(new Y(as...));
    }
}

#endif // _SHARED_HXX_
