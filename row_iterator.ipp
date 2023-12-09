template<typename T, size_t N, size_t M>
RowIterator<T, N, M>::RowIterator() {};

template<typename T, size_t N, size_t M>
RowIterator<T, N, M>::RowIterator(Matrix<T, N, M>& mat, size_t row) {
    row_ = row;
    matPtr = &mat;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::begin() {
    RowIterator tmp = *this;
    tmp.pos = 0;
    return tmp;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::end() {
    RowIterator tmp = *this;
    tmp.pos = M;
    return tmp;
}

template<typename T, size_t N, size_t M>
size_t RowIterator<T, N, M>::size() {
    return M;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M>& RowIterator<T, N, M>::operator+=(size_t i) {
    pos += i;
    return *this;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M>& RowIterator<T, N, M>::operator-=(size_t i) {
    pos -= i;
    return *this;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M>& RowIterator<T, N, M>::operator++() {
    ++pos;
    return *this;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::operator++(int) {
    RowIterator tmp = *this;
    ++pos;
    return tmp;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::operator+(size_t i) {
    RowIterator tmp = *this;
    tmp += i;
    return tmp;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::operator-(size_t i) {
    RowIterator tmp = *this;
    tmp -= i;
    return tmp;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M>& RowIterator<T, N, M>::operator--() {
    --pos;
    return *this;
}

template<typename T, size_t N, size_t M>
RowIterator<T, N, M> RowIterator<T, N, M>::operator--(int) {
    RowIterator tmp = *this;
    --pos;
    return tmp;
}

template<typename T, size_t N, size_t M>
T& RowIterator<T, N, M>::operator*() {
    return (*matPtr)[row_][pos];
}

template<typename T, size_t N, size_t M>
T& RowIterator<T, N, M>::operator[](size_t i) {
    return (*matPtr)[row_][pos + i];
}

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, RowIterator<T, N, M> row) {
    s << "[ ";
    for(auto e : row) {
        s << e << " ";
    }
    s << "]";
    return s;
}

template<typename T, size_t N, size_t M>
bool operator==(RowIterator<T, N, M> lhs, RowIterator<T, N, M> rhs) {
    return lhs.pos == rhs.pos;
}

template<typename T, size_t N, size_t M>
bool operator!=(RowIterator<T, N, M> lhs, RowIterator<T, N, M> rhs) {
    return lhs.pos != rhs.pos;
}