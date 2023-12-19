#include <iostream>
#include <array>
#include "matrix.hpp"
//#include "aes.hpp"
//#include "key_schedule.hpp"
#include "matrix_slice.hpp"
#include <vector>

// template <typename M, typename F>
// struct Iterator {
//     M dummy1 = 0;
//     F dummy2 = 1;
// };

// template<typename I>
// concept iterable = requires(I i) {
//     []<typename M, typename F>(Iterator<M, F>){}(i);
// };

// template<iterable I>
// void foo(I&& bar) {
//     //std::cout << bar.dummy1 << " " << bar.dummy2 << std::endl;
// }

int main() {
    int* ptr = new int(3);
    delete ptr;

    matrix::Matrix key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    matrix::Matrix A ({
        {0xde, 0xad, 0xbe, 0xef},
        {0xbe, 0xd0, 0x00, 0x00},
        {0xca, 0xfe, 0xba, 0xbe},
        {0x11, 0x11, 0x11, 0x11}
    });

    auto row1 = key.row(0);
    auto row2 = A.row(2);

    std::cout << std::hex << row1 << " " << row2 << std::endl;

    std::cout << std::hex << row1 << std::endl;
    row1.copy(row2);

    std::cout << std::hex << row1 << std::endl;
    row1 = row2;

    std::cout << std::hex << row1 << std::endl;

    //std::array<matrix::Matrix<int,4,4>, 11> roundKeys;
    //roundKeys[0] = key;

    //std::cout << std::hex << roundKeys[0] << std::endl;

    //for(int i = 1; i <= 10; i++) {
    //     roundKeys[i] = key_schedule::genRoundKey(roundKeys[i-1], i);
    //}

    // aes::addRoundKey(A, roundKeys[0]);
    // aes::encrypt::subBytes(A);
    // aes::encrypt::shiftRows(A);
    // aes::encrypt::mixColumns(A);
    // std::cout << std::hex << A << std::endl;

    // aes::decrypt::mixColumns(A);
    // aes::decrypt::shiftRows(A);
    // aes::decrypt::subBytes(A);
    // aes::addRoundKey(A, roundKeys[0]);
    // std::cout << std::hex << A << std::endl;
}