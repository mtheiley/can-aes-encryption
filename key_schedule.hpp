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

        for(size_t i = 1; i < N-1; i++) {
            generateKey(i);
        }
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

        std::cout << lmat << " " << rmat << std::endl;
        auto lhs = lmat.column(0);
        auto rhs = lmat.row(0);
        std::cout << lhs << " " << rhs << std::endl;


        //auto lhs1 = lmat.column(0);
        //auto lhs2 = lmat.column(1);
        //auto lhs3 = lmat.column(2);
        //auto lhs4 = lmat.column(3);

        //std::cout << lhs1 << std::endl;

        //auto rhs1 = rmat.column(0);
        //auto rhs2 = rmat.column(1);
        //auto rhs3 = rmat.column(2);
        //auto rhs4 = rmat.column(3);

        //std::cout << lhs1 << std::endl;
        return;

        //First Row
        //rhs1 = lhs4;
        //std::cout << rhs1 << std::endl;
        //rhs1.rotLeft(1);
        //std::cout << rhs1 << std::endl;
        //for(int j = 0; j < rhs1.size(); j++) {
        //    rhs1[j] = SubBox::encrypt(rhs1[j]);
        //}
        //std::cout << rhs1 << std::endl;
        //rhs1 ^= lhs1;
        //rhs1[0] ^= rcon(i);
        //std::cout << rhs1 << std::endl;

    }
    std::array<Matrix<T, 4, 4>, N> keys;
};

#endif //KEY_SCHEDULE