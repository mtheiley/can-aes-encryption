#ifndef ROW_ITERATOR_H
#define ROW_ITERATOR_H

#include <iostream>

template<typename T, size_t N, size_t M>
class Matrix;

template<typename T, size_t N, size_t M>
class RowIterator {
public:
    RowIterator();
    RowIterator(Matrix<T, N, M>& mat, size_t row);

    RowIterator begin();
    RowIterator end();
    size_t size();

    RowIterator& operator+=(size_t i);
    RowIterator& operator-=(size_t i);
    RowIterator& operator++();
    RowIterator operator++(int);
    RowIterator operator+(size_t i);
    RowIterator& operator--();
    RowIterator operator--(int);
    RowIterator operator-(size_t i);
    RowIterator& rotRight(size_t shift);
    RowIterator& rotLeft(size_t shift);
    
    T& operator*();
    T& at(size_t i);
    T& operator[](size_t i);

    template<typename T_, size_t N_, size_t M_>
    friend bool operator!=(RowIterator<T_, N_, M_> lhs, RowIterator<T_, N_, M_> rhs);
    template<typename T_, size_t N_, size_t M_>
    friend bool operator==(RowIterator<T_, N_, M_> lhs, RowIterator<T_, N_, M_> rhs);

private:
    size_t row_ = 0;
    size_t pos = 0;
    Matrix<T, N, M>* matPtr;
};

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, RowIterator<T, N, M> row);

template<typename T, size_t N, size_t M>
bool operator==(RowIterator<T, N, M> lhs, RowIterator<T, N, M> rhs);

template<typename T, size_t N, size_t M>
bool operator!=(RowIterator<T, N, M> lhs, RowIterator<T, N, M> rhs);

#include "row_iterator.ipp"

#endif //ROW_ITERATOR_H