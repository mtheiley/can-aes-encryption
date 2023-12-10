#ifndef MATRIX_ITERATOR_BASE_H
#define MATRIX_ITERATOR_BASE_H

#include <iostream>

template<typename T, size_t N, size_t M>
class Matrix;

template<typename T, typename V, typename M>
class MatrixIteratorBase {
public:
    virtual V begin();
    virtual V end();
    constexpr static size_t size() {return size_;}

    virtual V& operator+=(size_t i);
    virtual V& operator-=(size_t i);
    virtual V& operator++();
    virtual V operator++(int);
    virtual V operator+(size_t i);
    virtual V& operator--();
    virtual V operator--(int);
    virtual V operator-(size_t i);
    virtual V& operator^= (V& other);
    virtual V operator^(V& other);
    virtual V& rotRight(size_t shift);
    virtual V& rotLeft(size_t shift);

    virtual T& at(size_t i) {return dummy;}
    virtual T& operator*() {return dummy;}
    virtual T& operator[](size_t i) {return dummy;}
    virtual V& assign(V other);

protected:
    constexpr static size_t size_ = V::size();
    size_t pos = 0;
    M* matPtr;
    T dummy = T(0);
};

#include "matrix_iterator_base.ipp"

#endif //MATRIX_ITERATOR_BASE_H