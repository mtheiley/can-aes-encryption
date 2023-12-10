#ifndef COLUMN_ITERATOR_H
#define COLUMN_ITERATOR_H

#include <iostream>
#include "matrix_iterator_base.hpp"

template<typename T, typename M>
class ColumnIterator : public MatrixIteratorBase<T, ColumnIterator<T, M>, M> {
public:
    ColumnIterator();
    ColumnIterator(M& mat, size_t col);

    //size_t size();

    T& at(size_t i);
    T& operator*();
    T& operator[](size_t i);

    template<typename T_, typename M_>
    friend bool operator!=(ColumnIterator<T_, M_> lhs, ColumnIterator<T_, M_> rhs);
    template<typename T_, typename M_>
    friend bool operator==(ColumnIterator<T_, M_> lhs, ColumnIterator<T_, M_> rhs);

protected:
    static constexpr size_t size_ = M::size_N;

private:
    using MIB = MatrixIteratorBase<T, ColumnIterator<T, M>, M>;
    size_t col_ = 0;
};

template<typename T, typename M>
std::ostream& operator<<(std::ostream& s, ColumnIterator<T, M> column);

template<typename T, typename M>
bool operator==(ColumnIterator<T, M> lhs, ColumnIterator<T, M> rhs);

template<typename T, typename M>
bool operator!=(ColumnIterator<T, M> lhs, ColumnIterator<T, M> rhs);

#include "column_iterator.ipp"

#endif //COLUMN_ITERATOR_H