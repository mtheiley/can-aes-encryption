#ifndef AES_H
#define AES_H

#include "matrix.hpp"

namespace aes::encrypt {
    template<typename T>
    void mix(Matrix<T, 4, 4>& mat);

    template<typename T>
    void sub(Matrix<T, 4, 4>& mat);

    template<typename T>
    void shift(Matrix<T, 4, 4>& mat);
}

#include "aes.ipp"

#endif //AES_H