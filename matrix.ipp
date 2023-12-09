template<typename T, size_t M>
MatrixProxy_<T, M>::MatrixProxy_() {
    for(size_t i = 0; i < M; i++) {
        cells[i] = 0;
    }
}

template<typename T, size_t M>
MatrixProxy_<T, M>::MatrixProxy_(T(&&init)[M]) {
    for(int i = 0; i < M; i++) {
        cells[i] = init[i];
    }
}
template<typename T, size_t M>
std::array<T, M>::iterator MatrixProxy_<T, M>::begin() {
    return cells.begin();
}

template<typename T, size_t M>
std::array<T, M>::iterator MatrixProxy_<T, M>::end() {
    return cells.end();
}

template<typename T, size_t M>
size_t MatrixProxy_<T, M>::size() {
    return M;
}

template<typename T, size_t M>
T& MatrixProxy_<T, M>::operator[](size_t i) {
    return cells[i];
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>::Matrix() {
    for(size_t i = 0; i < N; i++) {
        rows[i] = MatrixProxy_<T,M>();
    }
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>::Matrix(Matrix<T, N, M>& other) {
    rows = std::array<MatrixProxy_<T,M>,N>(other.rows);
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>::Matrix(T(&&init)[N][M]) {
    for(size_t i = 0; i < N; i++) {
        rows[i] = MatrixProxy_<T,M>(std::move(init[i]));
    }
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> Matrix<T, N, M>::column(size_t i) {
    return ColumnIterator(*this, i);
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> Matrix<T, N, M>::row(size_t i) {
    return RowIterator(*this, i);
}

template<typename T, size_t N, size_t M>
std::array<MatrixProxy_<T,M>, N>::iterator Matrix<T, N, M>::begin() {
    return rows.begin();
}

template<typename T, size_t N, size_t M>
std::array<MatrixProxy_<T,M>, N>::iterator Matrix<T, N, M>::end() {
    return rows.end();
}

template<typename T, size_t N, size_t M>
size_t Matrix<T, N, M>::size() {
    return N;
}

template<typename T, size_t N, size_t M>
std::pair<size_t, size_t> Matrix<T, N, M>::dim() {
    return {N, M};
}

template<typename T, size_t N, size_t M>
MatrixProxy_<T, M>& Matrix<T, N, M>::operator[](size_t i) {
    return rows[i];
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(Matrix<T, N, M>& other) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            (*this)[i][j] += other[i][j];
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(Matrix<T, N, M>& other) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            (*this)[i][j] -= other[i][j];
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, Matrix<T, N, M> mat) {
    s << "[ ";
    for(auto row : mat) {
        s << "[ ";
        for(auto e : row) {
            s << e << " ";
        }
        s << "] "; 
    }
    s << "]";
    return s;
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M>& lhs, Matrix<T, N, M>& rhs) {
    Matrix<T, N, M> result;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            result[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return result;
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M>& lhs, Matrix<T, N, M>& rhs) {
    Matrix<T, N, M> result;
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            result[i][j] = lhs[i][j] - rhs[i][j];
        }
    }
    return result;
}

template<typename T, size_t N, size_t M, size_t P, size_t Q>
Matrix<T, N, Q> operator*(Matrix<T, N, M>& lhs, Matrix<T, P, Q>& rhs) {
    static_assert(M == P);
    Matrix<T, N, Q> result;
    
    for(int i = 0; i < N; i++) {
        auto row = lhs.row(i);
        for(int j = 0; j < Q; j++) {
            auto col = rhs.column(j);
            T sum = 0;
            for(int k = 0; k < row.size(); k++) {
                T left = *(row + k);
                T right = *(col + k);
                sum += left * right;
            }
            result[i][j] = sum;
        }
    }
    return result;
}