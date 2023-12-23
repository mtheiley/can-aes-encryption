template <typename T>
AES128<T>::AES128(matrix::Matrix<T,4,4>& key)
{
    generateRoundKeys(key);
}

template <typename T>
void AES128<T>::encrypt(matrix::Matrix<T,4,4>& data)
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

template <typename T>
void AES128<T>::decrypt(matrix::Matrix<T,4,4>& data)
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

template <typename T>
void AES128<T>::generateRoundKeys(matrix::Matrix<T,4,4>& key)
{
    roundKeys[0] = key;
    for(int i = 1; i <= 10; i++) {
         roundKeys[i] = key_schedule::genRoundKey(roundKeys[i-1], i);
    }
}
