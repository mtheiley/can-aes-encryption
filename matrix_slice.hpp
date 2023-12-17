#ifndef MATRIX_ITERATOR_PROTOTYPE
#define MATRIX_ITERATOR_PROTOTYPE

#include <iostream>

namespace matrix {
    template<typename M, typename F>
    class Iterator;
    template<typename M, typename F>
    class Slice;
}

template<typename I>
concept iterable = requires(I i) {
    []<typename M, typename F>(matrix::Iterator<M, F>){}(i);
};

template<typename M, typename F>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M, F>& slice);
template<iterable I, iterable J>
bool operator==(I&& lhs, J&& rhs);
template<iterable I, iterable J>
bool operator!=(I&& lhs, J&& rhs);

namespace matrix {
    using Point = std::pair<size_t, size_t>;

    auto columnIncrementor = [](Point point, size_t amount) {
        point.first+= amount;
        return point;
    };

    auto rowIncrementor = [](Point point, size_t amount) {
        point.second+= amount;
        return point;
    };

    template<typename M, typename F>
    class Slice {
    public:
        friend class Iterator<M, F>;

        Slice();
        Slice(Slice& other);
        Slice(M* matPtr, Point start, Point end, F incFunc);
        Slice& operator=(Slice& other);
        auto& operator[](size_t index);
        Slice& copy(Slice& other);
        auto begin();
        auto end();

    private:
        M* matPtr;
        F incFunc;
        Point start = {0, 0};
        Point end_ = {0, 0};
    };

    template<typename M, typename F>
    class Iterator {
    public:
        Iterator();
        Iterator(Slice<M, F>* slicePtr, Point offset, F incFunc);
        Iterator(Iterator& other);

        Iterator& operator=(Iterator& other);
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator+=(size_t i);
        Iterator operator+(size_t i);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator& operator-=(size_t i);
        Iterator operator-(size_t i);
        
        //Cannot seem to get friend function working so need method to do some work
        bool isSame(Iterator& other) {
            return slicePtr == other.slicePtr
            && offset.first == other.offset.first
            && offset.second == other.offset.second;
        }

        auto& operator*();
    private:
        Point offset = {0, 0};
        F incFunc;
        Slice<M, F>* slicePtr;
    };
}

#include "matrix_slice.ipp"

#endif //MATRIX_ITERATOR_PROTOTYPE