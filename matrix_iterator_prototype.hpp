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
    class Slice_Prototype {
    public:
        friend class Iterator;
        class Iterator {
        public:
            Iterator() {};
            Iterator(Slice_Prototype* slicePtr, Point offset, F incFunc) {
                this->slicePtr = slicePtr;
                this->incFunc = incFunc;
                this->offset = offset;
            }
            Iterator(Iterator& other) {
                offset = other.offset;
                incFunc = other.incFunc;
                slicePtr = other.slicePtr;
            }

            Iterator& operator=(Iterator& other) {
                offset = other.offset;
                incFunc = other.incFunc;
                slicePtr = other.slicePtr;
                return *this;
            }

            Iterator& operator++() {
                offset = incFunc(offset, 1);
                return *this;
            }

            Iterator operator++(int) {
                Iterator tmp = *this;
                offset = incFunc(offset, 1);
                return tmp;
            }

            Iterator& operator+=(size_t i) {
                offset = incFunc(offset, i);
                return *this;
            }

            Iterator operator+(size_t i) {
                Iterator tmp = *this;
                offset = incFunc(offset, i);
                return tmp;
            }

            Iterator& operator--() {
                offset = incFunc(offset, -1);
                return *this;
            }

            Iterator operator--(int) {
                Iterator tmp = *this;
                offset = incFunc(offset, -1);
                return tmp;
            }

            Iterator& operator-=(size_t i) {
                offset = incFunc(offset, -i);
                return *this;
            }

            Iterator operator-(size_t i) {
                Iterator tmp = *this;
                offset = incFunc(offset, -i);
                return tmp;
            }

            bool operator==(Iterator& other) {
                return slicePtr == other.slicePtr
                 && offset.first == other.offset.first
                 && offset.second == other.offset.second;
            }

            bool operator!=(Iterator& other) {
                return !(*this == other);
            }

            auto& operator*() {
                return (*(*slicePtr).matPtr)[offset.first][offset.second];
            }

        private:
            Point offset = {0, 0};
            F incFunc;
            Slice_Prototype* slicePtr;
        };

        Slice_Prototype() {};
        Slice_Prototype(Slice_Prototype& other) {
            matPtr = other.matPtr;
            start = other.start;
            end_ = other.end_;
            incFunc = other.incFunc;
        }
        Slice_Prototype(M* matPtr, Point start, Point end, F incFunc) {
            this->matPtr = matPtr;
            this->start = start;
            this->end_ = end;
            this->incFunc = incFunc;     
        }
        auto& operator=(Slice_Prototype& other) {
            matPtr = other.matPtr;
            start = other.start;
            end_ = other.end;
            incFunc = other.incFunc;
            return *this;
        }

        auto& operator[](size_t index) {
            auto offset = incFunc(start, index);
            return (*matPtr)[offset.first][offset.second];
        }

        Iterator begin() {
            return Iterator(this, start, incFunc);
        }

        Iterator end() {
            return Iterator(this, end_, incFunc);
        }

    private:
        M* matPtr;
        F incFunc;
        Point start = {0, 0};
        Point end_ = {0, 0};
    };
}

template<typename M, typename F>
std::ostream& operator<<(std::ostream& s, matrix::Slice_Prototype<M, F>& slice) {
    s << "[ ";
    for(auto e : slice) {
        s << e << " ";
    }
    s << "]";
    return s;
}

#endif //MATRIX_ITERATOR_PROTOTYPE