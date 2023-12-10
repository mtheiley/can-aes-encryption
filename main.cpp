#include <iostream>
#include "matrix.hpp"
#include "aes.hpp"
#include "key_schedule.hpp"

int main() {

    Matrix key ({
        {0xa0, 0x88, 0x23, 0x2a},
        {0xfa, 0x54, 0xa3, 0x6c},
        {0xfe, 0x2c, 0x39, 0x76},
        {0x17, 0xb1, 0x39, 0x05}
    });

    Matrix<int, 4, 4> A;
    
    std::cout << A << std::endl;
    A = Matrix({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });

    std::cout << A << std::endl;
    
    auto lhs = A.column(0);
    std::cout << lhs.at(0) << lhs.at(3) << std::endl;

    std::cout << "Size: " << lhs.size() << std::endl;
    
    std::cout << lhs << std::endl;

    //KeySchedule<int, 10> keySchedule(key);
}