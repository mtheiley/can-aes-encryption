#include "aes128.hpp"
#include "aes.hpp"
#include "key_schedule.hpp"

AES128::AES128(matrix::Matrix<int,4,4>& key)
{
    generateRoundKeys(key);
}

void AES128::encrypt(matrix::Matrix<int,4,4>& data)
{
    aes::addRoundKey(data, roundKeys[0]);

    for(int i = 1; i <= 9; ++i) {
        aes::encrypt::subBytes(data);
        aes::encrypt::shiftRows(data);
        aes::encrypt::mixColumns(data);
        aes::addRoundKey(data, roundKeys[i]);
    }

    aes::encrypt::subBytes(data);
    aes::encrypt::shiftRows(data);
    aes::addRoundKey(data, roundKeys[10]);
}

void AES128::decrypt(matrix::Matrix<int,4,4>& data)
{
    aes::addRoundKey(data, roundKeys[10]);
    aes::decrypt::shiftRows(data);
    aes::decrypt::subBytes(data);

    for(int i = 9; i > 0; --i) {
        aes::addRoundKey(data, roundKeys[i]);
        aes::decrypt::mixColumns(data);
        aes::decrypt::shiftRows(data);
        aes::decrypt::subBytes(data);
    }

    aes::addRoundKey(data, roundKeys[0]);
}

void AES128::generateRoundKeys(matrix::Matrix<int,4,4>& key)
{
    roundKeys[0] = key;
    for(int i = 1; i <= 10; i++) {
         roundKeys[i] = key_schedule::genRoundKey(roundKeys[i-1], i);
    }
}
