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
        size_t init_size_calculation();

        M& matRef;
        Point start = {0, 0};
        Point end_ = {0, 0};
        Point inc = {0, 0};

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

namespace matrix {
    template<typename M>
    Iterator<M>::Iterator() {};

    template<typename M>
    Iterator<M>::Iterator(Slice<M>& sliceRef, Point offset, Point inc) :
        sliceRef(sliceRef), offset(offset), inc(inc) {}

    template<typename M>
    Iterator<M>::Iterator(Iterator<M>& other) :
        sliceRef(other.sliceRef), offset(other.offset), inc(other.inc) {}

    template<typename M>
    Iterator<M>& Iterator<M>::operator=(Iterator<M>& other) {
        offset = other.offset;
        inc = other.inc;
        sliceRef = other.sliceRef;
        return *this;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator++() {
        offset = incFunc(offset, 1);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator++(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, 1);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator+=(size_t i) {
        offset = incFunc(offset, i);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator+(size_t i) {
        Iterator tmp = *this;
        tmp.offset = incFunc(offset, i);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator--() {
        offset = incFunc(offset, -1);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator--(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, -1);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator-=(size_t i) {
        offset = incFunc(offset, -i);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator-(size_t i) {
        Iterator tmp = *this;
        offset = incFunc(offset, -i);
        return tmp;
    }

    template<typename M>
    auto& Iterator<M>::operator*() {
        return sliceRef.matRef[offset.first][offset.second];
    }

    template<typename M>
    bool Iterator<M>::isSame(Iterator<M>& other) {
        return &sliceRef == &other.sliceRef
            && offset.first == other.offset.first
            && offset.second == other.offset.second;
    }

    template<typename M>
    Point Iterator<M>::incFunc(Point input, int i) {
        Point result = input;
        result.first += (inc.first) * i;
        result.second += (inc.second) * i;

        return result;
    }

    template<typename M>
    Slice<M>::Slice(M& matRef, Point start, Point end, Point inc) :
        matRef(matRef), start(start), end_(end), inc(inc) {
            
        size_ = init_size_calculation();
    }

    template<typename M>
    Slice<M>::Slice(Slice<M>& other) :
        matRef(other.matRef), start(other.start), end_(other.end_), inc(other.inc) {
        
        size_ = init_size_calculation();
    }

    template<typename M>
    size_t Slice<M>::init_size_calculation() {
        size_t size_first = 0;
        size_t size_second = 0; 
        
        if(inc.first != 0)
            size_first = (end_.first - start.first) / inc.first;
        if(inc.second != 0)
            size_second = (end_.second - start.second) / inc.second;

        if(size_first != 0 && size_second != 0) {
            return std::min(size_first, size_second);
        }
        if(size_first != 0) {
            return size_first;
        }
        return size_second;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator=(Slice<M>& other) {
        matRef = other.matRef;
        start = other.start;
        end_ = other.end_;
        inc = other.inc;
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator^=(Slice& other) {
        Iterator<M> left = Iterator(*this, start, inc);
        Iterator<M> right = Iterator(other, other.start, other.inc);

        while(left != end() && right != other.end()) {
            *left ^= *right;
            left++;
            right++;
        }

        if(left != end() || right != other.end()) {
            std::cout << "slice sizes incompatible" << std::endl;
            exit(1);
        }
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator<<(long k) {
        int numRounds = std::gcd(size(), k);
        for(int i = 0; i < numRounds; ++i) {
            int j = i;
            auto temp = (*this)[i];
        
            while (true) {
                int d = (j + k) % size();
                if (d==i) break;
                (*this)[j] = (*this)[d];
                j=d;
            }
            (*this)[j] = temp;
        }
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator>>(long k) { 
        (*this) << size() - k;
        return *this;
    }

    template<typename M>
    auto& Slice<M>::operator[](size_t index) {
        auto offset = start;
        offset.first += inc.first * index;
        offset.second += inc.second * index;
        return matRef[offset.first][offset.second];
    }

    template<typename M>
    Slice<M>& Slice<M>::copy(Slice<M>& other) {
        Iterator<M> left = Iterator<M>(*this, start, inc);
        Iterator<M> right = Iterator<M>(other, other.start, other.inc);

        while(left != end() && right != other.end()) {
            *left = *right;
            left++;
            right++;
        }

        if(left != end() || right != other.end()) {
            std::cout << "slice sizes incompatible" << std::endl;
            exit(1);
        }
        return *this;
    }

    template<typename M>
    size_t Slice<M>::size() {
        return size_;
    }

    template<typename M>
    auto Slice<M>::begin() {
        return Iterator(*this, start, inc);
    }

    template<typename M>
    auto Slice<M>::end() {
        return Iterator(*this, end_, inc);
    }
}

template<typename M>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M>& slice) {
    s << "[ ";
    for(auto e : slice) {
        s << e << " ";
    }
    s << "]";
    return s;
}

template<iterable I, iterable J>
bool operator==(I&& lhs, J&& rhs) {
    return lhs.isSame(rhs);
}

template<iterable I, iterable J>
bool operator!=(I&& lhs, J&& rhs) {
    return !(lhs == rhs);
}

#endif //MATRIX_SLICE