#ifndef SUB_BOX_H
#define SUB_BOX_H

#include <cstdint>

struct SubBox {
    static uint8_t encrypt(uint8_t value);
    static uint8_t decrypt(uint8_t value);
};

#endif //GALOIS_TABLE_H