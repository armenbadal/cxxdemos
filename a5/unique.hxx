#ifndef _UNIQUE_HXX_
#define _UNIQUE_HXX_

#include <cstddef>
#include <utility>

//
// Ռեսուրսին բացառիկ հասանելիություն ապահովող «խելացի» ցուցիչ։
// Նմանությամբ. https://en.cppreference.com/w/cpp/memory/unique_ptr
//
//
//
//
namespace unique {
    template<typename Y>
    class pointer {
    public:
        // լռելության կոնստրուկտոր
        pointer() = default;

        //// զրույական ցուցիչի կոնստրուկտոր
        //pointer(std::nullptr_t)
        //{}

        // հասարակ ցուցիչով կոնստրուկտոր
        pointer(Y* p)
            : _ptr{p}
        {}

        // պատճենող կոնստրուկտորը մեզ պետք չէ
        pointer(const pointer&) = delete;

        // տեղափոխող կոնստրուկտոր
        pointer(pointer&& other)
        {
            // յուրացնում ենք other-ի ռեսուրսը
            _ptr = std::exchange(other._ptr, nullptr);
        }

        // դեստրուկտորը ազատում է ռեսուրսը
        ~pointer()
        {
            delete _ptr;
        }

        // պատճենող վերագրումը նույնպես խանգարելու է մեզ
        pointer& operator=(const pointer&) = delete;

        // տեղափոխող վերագրումը
        pointer& operator=(pointer&& other)
        {
            // փոխատեղում. _ptr <-> other._ptr
            _ptr = std::exchange(other._ptr, _ptr);
        }

        // զրոյական ցուցիչի ստուգման համար
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

    private:
        Y* _ptr{nullptr};
    };
} // unique

#endif // UNIQUE_HXX_
