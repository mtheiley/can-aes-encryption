#include "galoistable.hpp"
#include "sub_box.hpp"

template<typename T>
void aes::encrypt::mix(Matrix<T, 4, 4>& mat) {
    using GT = GaloisTable;
    for(int i = 0; i < 4; i++)
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
void aes::encrypt::sub(Matrix<T, 4, 4>& mat) {
    for(auto& row : mat) {
        for(auto& e : row) {
            e = SubBox::encrypt(e);
        }
    }
}