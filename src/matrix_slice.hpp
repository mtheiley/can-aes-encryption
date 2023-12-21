#ifndef MATRIX_SLICE
#define MATRIX_SLICE

#include <iostream>
#include <numeric>

namespace matrix {
    template<typename M>
    class Iterator;
    template<typename M>
    class Slice;
}

template<typename I>
concept iterable = requires(I i) {
    []<typename M>(matrix::Iterator<M>){}(i);
};

template<typename M>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M>& slice);
template<iterable I, iterable J>
bool operator==(I&& lhs, J&& rhs);
template<iterable I, iterable J>
bool operator!=(I&& lhs, J&& rhs);

namespace matrix {
    using Point = std::pair<size_t, size_t>;

    static Point columnIncrementor = {1, 0};
    static Point rowIncrementor = {0, 1};

    template<typename M>
    class Slice {
    public:
        friend class Iterator<M>;

        Slice(Slice& other);
        Slice(M& matRef, Point start, Point end, Point inc);
        Slice& operator=(Slice& other);
        Slice& operator^=(Slice& other);
        Slice<M>& operator<<(long shift);
        Slice<M>& operator>>(long shift);
        auto& operator[](size_t index);
        Slice& copy(Slice& other);
        auto begin();
        auto end();
        size_t size();

    private:
        M& matRef;
        Point start = {0, 0};
        Point end_ = {0, 0};
        Point inc = {0, 0};

        bool size_cached = false; //avoid having to recalculate
        size_t size_;
    };

    template<typename M>
    class Iterator {
    public:
        Iterator();
        Iterator(Slice<M>& sliceRef, Point offset, Point inc);
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
        bool isSame(Iterator& other);

        Point incFunc(Point input, int i);

        auto& operator*();
    private:
        Point offset = {0, 0};
        Point inc = {0, 0};
        Slice<M>& sliceRef;
    };
}

#include "matrix_slice.ipp"

#endif //MATRIX_SLICE