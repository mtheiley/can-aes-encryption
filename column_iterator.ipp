template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>::ColumnIterator() {};

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>::ColumnIterator(Matrix<T, N, M>& mat, size_t col) {
    col_ = col;
    matPtr = &mat;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::begin() {
    auto tmp = *this;
    tmp.pos = 0;
    return tmp;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::end() {
    auto tmp = *this;
    tmp.pos = N;
    return tmp;
}

template<typename T, size_t N, size_t M>
size_t ColumnIterator<T, N, M>::size() {
    return N;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>& ColumnIterator<T, N, M>::operator+=(size_t i) {
    pos += i;
    return *this;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>& ColumnIterator<T, N, M>::operator-=(size_t i) {
    pos -= i;
    return *this;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>& ColumnIterator<T, N, M>::operator++() {
    ++pos;
    return *this;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::operator++(int) {
    ColumnIterator tmp = *this;
    ++pos;
    return tmp;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::operator+(size_t i) {
    ColumnIterator tmp = *this;
    tmp += i;
    return tmp;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::operator-(size_t i) {
    ColumnIterator tmp = *this;
    tmp -= i;
    return tmp;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M>& ColumnIterator<T, N, M>::operator--() {
    --pos;
    return *this;
}

template<typename T, size_t N, size_t M>
ColumnIterator<T, N, M> ColumnIterator<T, N, M>::operator--(int) {
    ColumnIterator tmp = *this;
    --pos;
    return tmp;
}

template<typename T, size_t N, size_t M>
T& ColumnIterator<T, N, M>::operator*() {
    return (*matPtr)[pos][col_];
}

template<typename T, size_t N, size_t M>
T& ColumnIterator<T, N, M>::operator[](size_t i) {
    return (*matPtr)[pos + i][col_];
}

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& s, ColumnIterator<T, N, M> column) {
    s << "[ ";
    for(auto e : column) {
        s << e << " ";
    }
    s << "]";
    return s;
}

template<typename T, size_t N, size_t M>
bool operator==(ColumnIterator<T, N, M> lhs, ColumnIterator<T, N, M> rhs) {
    return lhs.pos == rhs.pos;
}

template<typename T, size_t N, size_t M>
bool operator!=(ColumnIterator<T, N, M> lhs, ColumnIterator<T, N, M> rhs) {
    return lhs.pos != rhs.pos;
}