#ifndef KEY_SCHEDULE_H
#define KEY_SCHEDULE_H

#include <array>
#include "matrix.hpp"
#include "sub_box.hpp"

struct key_schedule {
    template<typename T, size_t N, size_t M>
    static Matrix<T, N, M> genRoundKey(Matrix<T, N, M>& prev, size_t roundNumber);

private:
    template<typename T>
    static T rcon(size_t i);
};

#include "key_schudule.ipp"

#endif //KEY_SCHEDULE