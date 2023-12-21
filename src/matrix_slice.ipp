namespace matrix {
    template<typename M>
    Iterator<M>::Iterator() {};

    template<typename M>
    Iterator<M>::Iterator(Slice<M>& sliceRef, Point offset, Point inc) :
        sliceRef(sliceRef), offset(offset), inc(inc) {}

    template<typename M>
    Iterator<M>::Iterator(Iterator<M>& other) :
        sliceRef(other.sliceRef), offset(other.offset), inc(other.inc) {}

    template<typename M>
    Iterator<M>& Iterator<M>::operator=(Iterator<M>& other) {
        offset = other.offset;
        inc = other.inc;
        sliceRef = other.sliceRef;
        return *this;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator++() {
        offset = incFunc(offset, 1);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator++(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, 1);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator+=(size_t i) {
        offset = incFunc(offset, i);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator+(size_t i) {
        Iterator tmp = *this;
        tmp.offset = incFunc(offset, i);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator--() {
        offset = incFunc(offset, -1);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator--(int) {
        Iterator tmp = *this;
        offset = incFunc(offset, -1);
        return tmp;
    }

    template<typename M>
    Iterator<M>& Iterator<M>::operator-=(size_t i) {
        offset = incFunc(offset, -i);
        return *this;
    }

    template<typename M>
    Iterator<M> Iterator<M>::operator-(size_t i) {
        Iterator tmp = *this;
        offset = incFunc(offset, -i);
        return tmp;
    }

    template<typename M>
    auto& Iterator<M>::operator*() {
        return sliceRef.matRef[offset.first][offset.second];
    }

    template<typename M>
    bool Iterator<M>::isSame(Iterator<M>& other) {
        return &sliceRef == &other.sliceRef
            && offset.first == other.offset.first
            && offset.second == other.offset.second;
    }

    template<typename M>
    Point Iterator<M>::incFunc(Point input, int i) {
        Point result = input;
        result.first += (inc.first) * i;
        result.second += (inc.second) * i;

        return result;
    }

    template<typename M>
    Slice<M>::Slice(M& matRef, Point start, Point end, Point inc) :
        matRef(matRef), start(start), end_(end), inc(inc) {}

    template<typename M>
    Slice<M>::Slice(Slice<M>& other) :
        matRef(other.matRef), start(other.start), end_(other.end_), inc(other.inc) {}

    template<typename M>
    Slice<M>& Slice<M>::operator=(Slice<M>& other) {
        matRef = other.matRef;
        start = other.start;
        end_ = other.end_;
        inc = other.inc;
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator^=(Slice& other) {
        Iterator<M> left = Iterator(*this, start, inc);
        Iterator<M> right = Iterator(other, other.start, other.inc);

        while(left != end() && right != other.end()) {
            *left ^= *right;
            left++;
            right++;
        }

        if(left != end() || right != other.end()) {
            std::cout << "slice sizes incompatible" << std::endl;
            exit(1);
        }
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator<<(long k) {
        int numRounds = std::gcd(size(), k);
        for(int i = 0; i < numRounds; ++i) {
            int j = i;
            auto temp = (*this)[i];
        
            while (true) {
                int d = (j + k) % size();
                if (d==i) break;
                (*this)[j] = (*this)[d];
                j=d;
            }
            (*this)[j] = temp;
        }
        return *this;
    }

    template<typename M>
    Slice<M>& Slice<M>::operator>>(long k) { 
        (*this) << size() - k;
        return *this;
    }

    template<typename M>
    auto& Slice<M>::operator[](size_t index) {
        //auto offset = incFunc(start, index);
        auto it = begin() + index;
        return *it;
    }

    template<typename M>
    Slice<M>& Slice<M>::copy(Slice<M>& other) {
        Iterator<M> left = Iterator<M>(*this, start, inc);
        Iterator<M> right = Iterator<M>(other, other.start, other.inc);

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

    template<typename M>
    size_t Slice<M>::size() {
        if(size_cached) return this->size_;
        
        size_t size_ = 0;
        for(auto _ : *this) ++size_;
        this->size_ = size_;
        size_cached = true;
        return size_;
    }

    template<typename M>
    auto Slice<M>::begin() {
        return Iterator(*this, start, inc);
    }

    template<typename M>
    auto Slice<M>::end() {
        return Iterator(*this, end_, inc);
    }
}

template<typename M>
std::ostream& operator<<(std::ostream& s, matrix::Slice<M>& slice) {
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