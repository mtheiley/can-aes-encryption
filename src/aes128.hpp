#ifndef AES_128_H
#define AES_128_H

#include <array>
#include "matrix.hpp"

class AES128 {
public:
    AES128(matrix::Matrix<int,4,4>& key);
    void encrypt(matrix::Matrix<int,4,4>& data);
    void decrypt(matrix::Matrix<int,4,4>& data);

private:
    void generateRoundKeys(matrix::Matrix<int,4,4>& key);
    std::array<matrix::Matrix<int,4,4>, 11> roundKeys;
};

#endif //AES_128_H