#ifndef COLUMN_ITERATOR_H
#define COLUMN_ITERATOR_H

#include <iostream>

template<typename T, size_t N, size_t M>
class Matrix;

template<typename T, size_t N, size_t M>
class ColumnIterator {
public:
    ColumnIterator();
    ColumnIterator(Matrix<T, N, M>& mat, size_t col);

    ColumnIterator begin();
    ColumnIterator end();
    size_t size();

    ColumnIterator& operator+=(size_t i);
    ColumnIterator& operator-=(size_t i);
    ColumnIterator& operator++();
    ColumnIterator operator++(int);
    ColumnIterator operator+(size_t i);
    ColumnIterator& operator--();
    ColumnIterator operator--(int);
    ColumnIterator operator-(size_t i);
    T& operator*();
    T& operator[](size_t);

    template<typename T_, size_t N_, size_t M_>
    friend bool operator!=(ColumnIterator<T_, N_, M_> lhs, ColumnIterator<T_, N_, M_> rhs);
    template<typename T_, size_t N_, size_t M_>
    friend bool operator==(ColumnIterator<T_, N_, M_> lhs, ColumnIterator<T_, N_, M_> rhs);

private:
    size_t col_ = 0;
    size_t pos = 0;
    Matrix<T, N, M>* matPtr;
};

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, ColumnIterator<T, N, M> column);

template<typename T, size_t N, size_t M>
bool operator==(ColumnIterator<T, N, M> lhs, ColumnIterator<T, N, M> rhs);

template<typename T, size_t N, size_t M>
bool operator!=(ColumnIterator<T, N, M> lhs, ColumnIterator<T, N, M> rhs);

#include "column_iterator.ipp"

#endif //COLUMN_ITERATOR_H