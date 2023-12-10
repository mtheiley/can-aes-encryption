#include <iostream>
#include "matrix.hpp"
#include "aes.hpp"
#include "key_schedule.hpp"

int main() {

    Matrix key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    Matrix A ({
        {0xde, 0xad, 0xbe, 0xef},
        {0xbe, 0xd0, 0x00, 0x00},
        {0xca, 0xfe, 0xba, 0xbe},
        {0x11, 0x11, 0x11, 0x11}
    });

    KeySchedule<int, 10> keySchedule(key);

    aes::addRoundKey(A, keySchedule.getKey(0));
    aes::encrypt::subBytes(A);
    aes::encrypt::shiftRows(A);
    aes::encrypt::mixColumns(A);
    std::cout << std::hex << A << std::endl;

    aes::decrypt::mixColumns(A);
    aes::decrypt::shiftRows(A);
    aes::decrypt::subBytes(A);
    aes::addRoundKey(A, keySchedule.getKey(0));
    std::cout << std::hex << A << std::endl;
}