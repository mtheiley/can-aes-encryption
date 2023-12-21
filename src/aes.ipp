#include "galoistable.hpp"
#include "sub_box.hpp"

template<typename T>
void aes::addRoundKey(matrix::Matrix<T, 4, 4>& mat, matrix::Matrix<T, 4, 4>& roundKey) {
    
    for(int i = 0; i < mat.dim().second; i++) {
        auto lhs = mat.column(i);
        auto rhs = roundKey.column(i);

        for(int j = 0; j < lhs.size(); j++) {
            lhs[j] ^= rhs[j];
        }
    }
}

template<typename T>
void aes::encrypt::mixColumns(matrix::Matrix<T, 4, 4>& mat) {
    using GT = GaloisTable;
    for(int i = 0; i < mat.dim().second; i++)
    {
        auto col = mat.column(i);
        
        auto c1 = GT::gfield2(col[0]) ^ GT::gfield3(col[1]) ^ col[2] ^ col[3];
        auto c2 = col[0] ^ GT::gfield2(col[1]) ^ GT::gfield3(col[2]) ^ col[3];
        auto c3 = col[0] ^ col[1] ^ GT::gfield2(col[2]) ^ GT::gfield3(col[3]);
        auto c4 = GT::gfield3(col[0]) ^ col[1] ^ col[2] ^ GT::gfield2(col[3]);
    
        col[0] = c1;
        col[1] = c2;
        col[2] = c3;
        col[3] = c4;
    }
}

template<typename T>
void aes::encrypt::subBytes(matrix::Matrix<T, 4, 4>& mat) {
    for(auto& row : mat) {
        for(auto& e : row) {
            e = SubBox::encrypt(e);
        }
    }
}

template<typename T>
void aes::encrypt::shiftRows(matrix::Matrix<T, 4, 4>& mat) {
    mat.row(1).rotRight(1);
    mat.row(2).rotRight(2);
    mat.row(3).rotRight(3);
}

template<typename T>
void aes::decrypt::mixColumns(matrix::Matrix<T, 4, 4>& mat) {
    using GT = GaloisTable;
    for(int i = 0; i < mat.dim().second; i++)
    {
        auto col = mat.column(i);
        
        auto c1 = GT::gfield14(col[0]) ^ GT::gfield11(col[1]) ^ GT::gfield13(col[2]) ^ GT::gfield9(col[3]);
        auto c2 = GT::gfield9(col[0]) ^ GT::gfield14(col[1]) ^ GT::gfield11(col[2]) ^ GT::gfield13(col[3]);
        auto c3 = GT::gfield13(col[0]) ^ GT::gfield9(col[1]) ^ GT::gfield14(col[2]) ^ GT::gfield11(col[3]);
        auto c4 = GT::gfield11(col[0]) ^ GT::gfield13(col[1]) ^ GT::gfield9(col[2]) ^ GT::gfield14(col[3]);
    
        col[0] = c1;
        col[1] = c2;
        col[2] = c3;
        col[3] = c4;
    }
}

template<typename T>
void aes::decrypt::subBytes(matrix::Matrix<T, 4, 4>& mat) {
    for(auto& row : mat) {
        for(auto& e : row) {
            e = SubBox::decrypt(e);
        }
    }
}

template<typename T>
void aes::decrypt::shiftRows(matrix::Matrix<T, 4, 4>& mat) {
    mat.row(1).rotLeft(1);
    mat.row(2).rotLeft(2);
    mat.row(3).rotLeft(3);
}