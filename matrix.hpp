#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include "column_iterator.hpp"
#include "row_iterator.hpp"

template<typename T, size_t N, size_t M>
class Matrix;

template<typename T, size_t M>
class MatrixProxy_ {
public:
    MatrixProxy_();
    MatrixProxy_(T(&&init)[M]);

    std::array<T, M>::iterator begin();
    std::array<T, M>::iterator end();
    size_t size();
    T& operator[](size_t i);

private:
    std::array<T, M> cells;
};

template<typename T, size_t N, size_t M>
class Matrix {
public:
    Matrix();
    Matrix(Matrix<T, N, M>& other);
    explicit Matrix(T(&&init)[N][M]);

    ColumnIterator<T, N, M> column(size_t i);
    RowIterator<T, N, M> row(size_t i);

    std::array<MatrixProxy_<T,M>, N>::iterator begin();
    std::array<MatrixProxy_<T,M>, N>::iterator end();
    size_t size();
    std::pair<size_t, size_t> dim();

    MatrixProxy_<T, M>& operator[](size_t i);
    Matrix<T, N, M>& operator+=(Matrix<T, N, M>& other);
    Matrix<T, N, M>& operator-=(Matrix<T, N, M>& other);

private:
    std::array<MatrixProxy_<T, M>, N> rows;
};

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, Matrix<T, N, M> mat);

template<typename T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M>& lhs, Matrix<T, N, M>& rhs);

template<typename T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M>& lhs, Matrix<T, N, M>& rhs);

template<typename T, size_t N, size_t M, size_t P, size_t Q>
Matrix<T, N, Q> operator*(Matrix<T, N, M>& lhs, Matrix<T, P, Q>& rhs);

#include "matrix.ipp"

#endif //MATRIX_H