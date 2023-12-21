#ifndef AES_H
#define AES_H

#include "matrix.hpp"

namespace aes {
    template<typename T>
    void addRoundKey(matrix::Matrix<T, 4, 4>& mat, matrix::Matrix<T, 4, 4>& roundKey);
}

namespace aes::encrypt {
    template<typename T>
    void mixColumns(matrix::Matrix<T, 4, 4>& mat);

    template<typename T>
    void subBytes(matrix::Matrix<T, 4, 4>& mat);

    template<typename T>
    void shiftRows(matrix::Matrix<T, 4, 4>& mat);
}

namespace aes::decrypt {
    template<typename T>
    void mixColumns(matrix::Matrix<T, 4, 4>& mat);

    template<typename T>
    void subBytes(matrix::Matrix<T, 4, 4>& mat);

    template<typename T>
    void shiftRows(matrix::Matrix<T, 4, 4>& mat);
}

#include "aes.ipp"

#endif //AES_H