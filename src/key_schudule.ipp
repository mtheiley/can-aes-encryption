template<typename T>
T key_schedule::rcon(size_t i) {
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

template<typename T, size_t N, size_t M>
Matrix<T, N, M> key_schedule::genRoundKey(Matrix<T, N, M>& prev, size_t roundNumber) {
    Matrix<T, N, M> key;

    //First Row
    auto rhs1 = key.column(0);
    auto lhs1 = prev.column(0);
    auto lhsLast = prev.column(M - 1);
    rhs1.copy(lhsLast);
    rhs1.rotLeft(1);
    for(int j = 0; j < rhs1.size(); j++) {
        rhs1[j] = SubBox::encrypt(rhs1[j]);
    }
    rhs1 ^= lhs1;
    rhs1[0] ^= key_schedule::rcon<T>(roundNumber);

    //Others
    auto rhsPrev = rhs1;
    for(size_t i = 1; i < M; i++) {
        auto rhs = key.column(i);
        auto lhs = prev.column(i);
        rhs.copy(rhsPrev);
        rhs ^= lhs;
        rhsPrev = rhs;
    }

    return key;
}