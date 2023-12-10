template<typename T, typename M>
RowIterator<T, M>::RowIterator() {};

template<typename T, typename M>
RowIterator<T, M>::RowIterator(M& mat, size_t row) {
    row_ = row;
    MIB::matPtr = &mat;
}

//template<typename T, typename M>
//size_t RowIterator<T, M>::size() {
//    return MIB::matPtr->dim().second;
//}

template<typename T, typename M>
T& RowIterator<T, M>::at(size_t i) {
    return (*MIB::matPtr)[row_][MIB::pos + i];
}

template<typename T, typename M>
T& RowIterator<T, M>::operator*() {
    return (*MIB::matPtr)[row_][MIB::pos];
}

template<typename T, typename M>
T& RowIterator<T, M>::operator[](size_t i) {
    return (*MIB::matPtr)[row_][MIB::pos + i];
}

template<typename T, typename M>
std::ostream& operator<<(std::ostream& s, RowIterator<T, M> column) {
    s << "[ ";
    for(auto e : column) {
        s << e << " ";
    }
    s << "]";
    return s;
}

template<typename T, typename M>
bool operator==(RowIterator<T, M> lhs, RowIterator<T, M> rhs) {
    return lhs.pos == rhs.pos;
}

template<typename T, typename M>
bool operator!=(RowIterator<T, M> lhs, RowIterator<T, M> rhs) {
    return lhs.pos != rhs.pos;
}