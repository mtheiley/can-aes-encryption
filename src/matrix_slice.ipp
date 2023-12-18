namespace matrix {
    template<typename M, typename F>
    Iterator<M, F>::Iterator() {};

    template<typename M, typename F>
    Iterator<M, F>::Iterator(Slice<M, F>* slicePtr, Point offset, F incFunc) {
        this->slicePtr = slicePtr;
        this->incFunc = incFunc;
        this->offset = offset;
    }

    template<typename M, typename F>
    Iterator<M, F>::Iterator(Iterator<M, F>& other) {
        offset = other.offset;
        incFunc = other.incFunc;
        slicePtr = other.slicePtr;
    }

    template<typename M, typename F>
    Iterator<M, F>& Iterator<M, F>::operator=(Iterator<M, F>& other) {
        offset = other.offset;
        incFunc = other.incFunc;
        slicePtr = other.slicePtr;
        return *this;
    }

    template<typename M, typename F>
    Iterator<M, F>& Iterator<M, F>::operator++() {
        offset = incFunc(offset, 1);
        return *this;
    }

    template<typename M, typename F>
    Iterator<M, F> Iterator<M, F>::operator++(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, 1);
        return tmp;
    }

    template<typename M, typename F>
    Iterator<M, F>& Iterator<M, F>::operator+=(size_t i) {
        offset = incFunc(offset, i);
        return *this;
    }

    template<typename M, typename F>
    Iterator<M, F> Iterator<M, F>::operator+(size_t i) {
        Iterator tmp = *this;
        offset = incFunc(offset, i);
        return tmp;
    }

    template<typename M, typename F>
    Iterator<M, F>& Iterator<M, F>::operator--() {
        offset = incFunc(offset, -1);
        return *this;
    }

    template<typename M, typename F>
    Iterator<M, F> Iterator<M, F>::operator--(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, -1);
        return tmp;
    }

    template<typename M, typename F>
    Iterator<M, F>& Iterator<M, F>::operator-=(size_t i) {
        offset = incFunc(offset, -i);
        return *this;
    }

    template<typename M, typename F>
    Iterator<M, F> Iterator<M, F>::operator-(size_t i) {
        Iterator tmp = *this;
        offset = incFunc(offset, -i);
        return tmp;
    }

    template<typename M, typename F>
    auto& Iterator<M, F>::operator*() {
        return (*(*slicePtr).matPtr)[offset.first][offset.second];
    }

    template<typename M, typename F>
    Slice<M, F>::Slice() {};

    template<typename M, typename F>
    Slice<M, F>::Slice(Slice<M, F>& other) {
        matPtr = other.matPtr;
        start = other.start;
        end_ = other.end_;
        incFunc = other.incFunc;
    }

    template<typename M, typename F>
    Slice<M, F>::Slice(M* matPtr, Point start, Point end, F incFunc) {
        this->matPtr = matPtr;
        this->start = start;
        this->end_ = end;
        this->incFunc = incFunc;     
    }

    template<typename M, typename F>
    Slice<M, F>& Slice<M, F>::operator=(Slice<M, F>& other) {
        matPtr = other.matPtr;
        start = other.start;
        end_ = other.end_;
        incFunc = other.incFunc;
        return *this;
    }

    template<typename M, typename F>
    auto& Slice<M, F>::operator[](size_t index) {
        auto offset = incFunc(start, index);
        return (*matPtr)[offset.first][offset.second];
    }

    template<typename M, typename F>
    Slice<M, F>& Slice<M, F>::copy(Slice<M, F>& other) {
        Iterator<M, F> left = Iterator(this, start, incFunc);
        Iterator<M, F> right = Iterator(&other, other.start, other.incFunc);

        while(left != end() && right != other.end()) {
            *left = *right;
            left++;
            right++;
        }

        if(left != end() || right != other.end()) {
            std::cout << "slice sizes incompatible" << std::endl;
            exit(1);
        }
        return *this;
    }

    template<typename M, typename F>
    auto Slice<M, F>::begin() {
        return Iterator(this, start, incFunc);
    }

    template<typename M, typename F>
    auto Slice<M, F>::end() {
        return Iterator(this, end_, incFunc);
    }
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

template<iterable I, iterable J>
bool operator==(I&& lhs, J&& rhs) {
    return lhs.isSame(rhs);
}

template<iterable I, iterable J>
bool operator!=(I&& lhs, J&& rhs) {
    return !(lhs == rhs);
}