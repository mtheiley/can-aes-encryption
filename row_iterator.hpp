#ifndef ROW_ITERATOR_H
#define ROW_ITERATOR_H

#include <iostream>
#include "matrix_iterator_base.hpp"

template<typename T, typename M>
class RowIterator : public MatrixIteratorBase<T, RowIterator<T, M>, M>{
public:
    RowIterator();
    RowIterator(M& mat, size_t row);

    constexpr static size_t size() {return size_;}
    
    T& at(size_t i);
    T& operator*();
    T& operator[](size_t i);

    template<typename T_, typename M_>
    friend bool operator!=(RowIterator<T_, M_> lhs, RowIterator<T_, M_> rhs);
    template<typename T_, typename M_>
    friend bool operator==(RowIterator<T_, M_> lhs, RowIterator<T_, M_> rhs);

protected:
    static constexpr size_t size_ = M::size_M;

private:
    using MIB = MatrixIteratorBase<T, RowIterator<T, M>, M>;
    size_t row_ = 0;
};

template<typename T, typename M>
std::ostream& operator<<(std::ostream& s, RowIterator<T, M> column);

template<typename T, typename M>
bool operator==(RowIterator<T, M> lhs, RowIterator<T, M> rhs);

template<typename T, typename M>
bool operator!=(RowIterator<T, M> lhs, RowIterator<T, M> rhs);

#include "row_iterator.ipp"

#endif //ROW_ITERATOR_H