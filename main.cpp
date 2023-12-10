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

    KeySchedule<int, 10> keySchedule(key);
    for(int i = 0; i <= 10; i++) {
        std::cout << std::hex << keySchedule.getKey(i) << std::endl;
    }
}