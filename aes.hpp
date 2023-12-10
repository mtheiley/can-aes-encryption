#ifndef AES_H
#define AES_H

#include "matrix.hpp"

namespace aes {
    template<typename T>
    void addRoundKey(Matrix<T, 4, 4>& mat, Matrix<T, 4, 4>& roundKey);
}

namespace aes::encrypt {
    template<typename T>
    void mixColumns(Matrix<T, 4, 4>& mat);

    template<typename T>
    void subBytes(Matrix<T, 4, 4>& mat);

    template<typename T>
    void shiftRows(Matrix<T, 4, 4>& mat);
}

namespace aes::decrypt {
    template<typename T>
    void mixColumns(Matrix<T, 4, 4>& mat);

    template<typename T>
    void subBytes(Matrix<T, 4, 4>& mat);

    template<typename T>
    void shiftRows(Matrix<T, 4, 4>& mat);
}

#include "aes.ipp"

#endif //AES_H