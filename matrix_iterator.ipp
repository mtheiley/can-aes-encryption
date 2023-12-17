
template<typename M, typename F>
matrix::Slice<M, F>::Iterator::Iterator() {};

template<typename M, typename F>
matrix::Slice<M, F>::Iterator::Iterator(Slice<M,F>* slicePtr, Point offset, F incFunc) {
    this->slicePtr = slicePtr;
    this->incFunc = incFunc;
    this->offset = offset;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator::Iterator(matrix::Slice<M, F>::Iterator& other) {
    offset = other.offset;
    incFunc = other.incFunc;
    slicePtr = other.slicePtr;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator& matrix::Slice<M, F>::Iterator::operator=(matrix::Slice<M, F>::Iterator& other) {
    offset = other.offset;
    incFunc = other.incFunc;
    slicePtr = other.slicePtr;
    return *this;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator& matrix::Slice<M, F>::Iterator::operator++() {
    offset = incFunc(offset, 1);
    return *this;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::Iterator::operator++(int) {
    Iterator tmp = *this;
    offset = incFunc(offset, 1);
    return tmp;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator& matrix::Slice<M, F>::Iterator::operator+=(size_t i) {
    offset = incFunc(offset, i);
    return *this;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::Iterator::operator+(size_t i) {
    Iterator tmp = *this;
    offset = incFunc(offset, i);
    return tmp;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator& matrix::Slice<M, F>::Iterator::operator--() {
    offset = incFunc(offset, -1);
    return *this;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::Iterator::operator--(int) {
    Iterator tmp = *this;
    offset = incFunc(offset, -1);
    return tmp;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator& matrix::Slice<M, F>::Iterator::operator-=(size_t i) {
    offset = incFunc(offset, -i);
    return *this;
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::Iterator::operator-(size_t i) {
    Iterator tmp = *this;
    offset = incFunc(offset, -i);
    return tmp;
}

template<typename M, typename F>
bool matrix::Slice<M, F>::Iterator::operator==(matrix::Slice<M, F>::Iterator& other) {
    return slicePtr == other.slicePtr
        && offset.first == other.offset.first
        && offset.second == other.offset.second;
}

template<typename M, typename F>
bool matrix::Slice<M, F>::Iterator::operator!=(matrix::Slice<M, F>::Iterator& other) {
    return !(*this == other);
}

template<typename M, typename F>
auto& matrix::Slice<M, F>::Iterator::operator*() {
    return (*(*slicePtr).matPtr)[offset.first][offset.second];
}

template<typename M, typename F>
matrix::Slice<M, F>::Slice() {};

template<typename M, typename F>
matrix::Slice<M, F>::Slice(matrix::Slice<M, F>& other) {
    matPtr = other.matPtr;
    start = other.start;
    end_ = other.end_;
    incFunc = other.incFunc;
}

template<typename M, typename F>
matrix::Slice<M, F>::Slice(M* matPtr, Point start, Point end, F incFunc) {
    this->matPtr = matPtr;
    this->start = start;
    this->end_ = end;
    this->incFunc = incFunc;     
}

template<typename M, typename F>
auto& matrix::Slice<M, F>::operator=(matrix::Slice<M, F>& other) {
    matPtr = other.matPtr;
    start = other.start;
    end_ = other.end;
    incFunc = other.incFunc;
    return *this;
}

template<typename M, typename F>
auto& matrix::Slice<M, F>::operator[](size_t index) {
    auto offset = incFunc(start, index);
    return (*matPtr)[offset.first][offset.second];
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::begin() {
    return Iterator(this, start, incFunc);
}

template<typename M, typename F>
matrix::Slice<M, F>::Iterator matrix::Slice<M, F>::end() {
    return Iterator(this, end_, incFunc);
}

template<typename M, typename F>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M, F>& slice) {
    s << "[ ";
    for(auto e : slice) {
        s << e << " ";
    }
    s << "]";
    return s;
}