#ifndef KEY_SCHEDULE_H
#define KEY_SCHEDULE_H

#include <array>
#include "matrix.hpp"
#include "sub_box.hpp"

template<typename T, size_t N>
class KeySchedule {
public:
    KeySchedule() {};
    KeySchedule(Matrix<T, 4, 4> initKey) {
        keys[0] = initKey;
        for(size_t i = 1; i <= N; i++) {
            generateKey(i);
        }
    }
    Matrix<T, 4, 4>& getKey(size_t i) {
        return keys[i];
    }
    
private:
    T rcon(size_t i) {
        switch(i) {
            case 1:
                return 0x01;
            case 2:
                return 0x02;
            case 3:
                return 0x04;
            case 4:
                return 0x08;
            case 5:
                return 0x10;
            case 6:
                return 0x20;
            case 7:
                return 0x40;
            case 8:
                return 0x80;
            case 9:
                return 0x1b;
            case 10:
                return 0x36;
            default:
                return 0;
        }
    }

    void generateKey(size_t i) {
        auto& lmat = keys[i-1];
        auto& rmat = keys[i];

        auto lhs1 = lmat.column(0);
        auto lhs2 = lmat.column(1);
        auto lhs3 = lmat.column(2);
        auto lhs4 = lmat.column(3);

        auto rhs1 = rmat.column(0);
        auto rhs2 = rmat.column(1);
        auto rhs3 = rmat.column(2);
        auto rhs4 = rmat.column(3);

        //First Row
        rhs1 = lhs4;
        rhs1.rotLeft(1);
        for(int j = 0; j < rhs1.size(); j++) {
           rhs1[j] = SubBox::encrypt(rhs1[j]);
        }
        rhs1 ^= lhs1;
        rhs1[0] ^= rcon(i);

        //Others
        rhs2 = rhs1;
        rhs2 ^= lhs2;
        rhs3 = rhs2;
        rhs3 ^= lhs3;
        rhs4 = rhs3;
        rhs4 ^= lhs4;
    }
    std::array<Matrix<T, 4, 4>, N+1> keys;
};

#endif //KEY_SCHEDULE