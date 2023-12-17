#ifndef MATRIX_ITERATOR_PROTOTYPE
#define MATRIX_ITERATOR_PROTOTYPE

#include <iostream>

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
        friend class Iterator;
        class Iterator {
        public:
            Iterator();
            Iterator(Slice* slicePtr, Point offset, F incFunc);
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
            bool operator==(Iterator& other);
            bool operator!=(Iterator& other);
            auto& operator*();

        private:
            Point offset = {0, 0};
            F incFunc;
            Slice* slicePtr;
        };

        Slice();
        Slice(Slice& other);
        Slice(M* matPtr, Point start, Point end, F incFunc);
        auto& operator=(Slice& other);
        auto& operator[](size_t index);
        Iterator begin();
        Iterator end();

    private:
        M* matPtr;
        F incFunc;
        Point start = {0, 0};
        Point end_ = {0, 0};
    };
}

template<typename M, typename F>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M, F>& slice);

#include "matrix_iterator.ipp"

#endif //MATRIX_ITERATOR_PROTOTYPE