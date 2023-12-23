#ifndef AES_128_H
#define AES_128_H

#include <array>
#include "matrix.hpp"
#include "aes.hpp"
#include "key_schedule.hpp"

template <typename T>
class AES128 {
public:
    AES128(matrix::Matrix<T,4,4>& key);
    void encrypt(matrix::Matrix<T,4,4>& data);
    void decrypt(matrix::Matrix<T,4,4>& data);

private:
    void generateRoundKeys(matrix::Matrix<T,4,4>& key);
    std::array<matrix::Matrix<T,4,4>, 11> roundKeys;
};

#include "aes128.ipp"

#endif //AES_128_H