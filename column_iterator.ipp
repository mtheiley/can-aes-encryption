template<typename T, typename M>
ColumnIterator<T, M>::ColumnIterator() {};

template<typename T, typename M>
ColumnIterator<T, M>::ColumnIterator(M& mat, size_t col) {
    col_ = col;
    MIB::matPtr = &mat;
}

//template<typename T, typename M>
//size_t ColumnIterator<T, M>::size() {
//    return MIB::matPtr->dim().first;
//}

template<typename T, typename M>
T& ColumnIterator<T, M>::at(size_t i) {
    return (*MIB::matPtr)[MIB::pos + i][col_];
}

template<typename T, typename M>
T& ColumnIterator<T, M>::operator*() {
    return (*MIB::matPtr)[MIB::pos][col_];
}

template<typename T, typename M>
T& ColumnIterator<T, M>::operator[](size_t i) {
    return (*MIB::matPtr)[MIB::pos + i][col_];
}

template<typename T, typename M>
std::ostream& operator<<(std::ostream& s, ColumnIterator<T, M> column) {
    s << "[ ";
    for(auto e : column) {
        s << e << " ";
    }
    s << "]";
    return s;
}

template<typename T, typename M>
bool operator==(ColumnIterator<T, M> lhs, ColumnIterator<T, M> rhs) {
    return lhs.pos == rhs.pos;
}

template<typename T, typename M>
bool operator!=(ColumnIterator<T, M> lhs, ColumnIterator<T, M> rhs) {
    return lhs.pos != rhs.pos;
}