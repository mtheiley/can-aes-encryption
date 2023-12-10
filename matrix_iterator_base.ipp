template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::begin() {
    auto tmp = *static_cast<V*>(this);
    tmp.pos = 0;
    return tmp;
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::end() {
    auto tmp = *static_cast<V*>(this);
    tmp.pos = size();
    return tmp;
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::operator+=(size_t i) {
    pos += i;
    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::operator-=(size_t i) {
    pos -= i;
    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::operator++() {
    ++pos;
    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::operator++(int) {
    V tmp = *static_cast<V*>(this);
    ++pos;
    return tmp;
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::operator+(size_t i) {
    V tmp = *static_cast<V*>(this);
    tmp += i;
    return tmp;
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::operator-(size_t i) {
    V tmp = *static_cast<V*>(this);
    tmp -= i;
    return tmp;
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::operator--() {
    --pos;
    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::operator--(int) {
    V tmp = *static_cast<V*>(this);
    --pos;
    return tmp;
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::operator^=(V& other) {
    for(int i = 0; i < size(); i++) {
        at(i) ^= other.at(i);
    }
    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V MatrixIteratorBase<T, V, M>::operator^(V& other) {
    V tmp = *static_cast<V*>(this);
    
    for(int i = 0; i < size(); i++) {
        tmp.at(i) ^= other.at(i);
    }
    return tmp;
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::rotRight(size_t shift) {
    auto elementOffset = [this](int start_, int shift_){
        shift_ %= size();
        int offset = start_ + shift_;
        offset %= size();
        return offset;
    };
    
    std::array<T, size()> copy;
    for(int i = 0; i < size(); i++) {
        copy[i] = at(i);
    }

    for(int i = 0; i < size(); i++) {
        at(elementOffset(i, shift)) = copy[i];
    }

    return *static_cast<V*>(this);
}

template<typename T, typename V, typename M>
V& MatrixIteratorBase<T, V, M>::rotLeft(size_t shift) {
    auto elementOffset = [this](int start_, int shift_){
        shift_ %= size();
        int offset = start_ - shift_;
        if(offset < 0) {
            offset += (int) size();
        }
        return offset;
    };
    
    std::array<T, size()> copy;
    for(int i = 0; i < size(); i++) {
        copy[i] = at(i);
    }

    for(int i = 0; i < size(); i++) {
        at(elementOffset(i, shift)) = copy[i];
    }

    return *static_cast<V*>(this);
}