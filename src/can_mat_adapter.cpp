#include "can_mat_adapter.hpp"

namespace can_mat_adapter {
    matrix::Matrix<uint8_t, 4, 4> canToMat(can_frame frame) {
        uint8_t can_id_1 = 0xFF & frame.can_id;
        uint8_t can_id_2 = 0xFF & (frame.can_id >> 8);
        uint8_t can_id_3 = 0xFF & (frame.can_id >> 16);
        uint8_t can_id_4 = 0xFF & (frame.can_id >> 24);

        std::array<uint8_t, 8> can_data;
        for(size_t i = 0; i < frame.can_dlc; i++) {
            can_data[i] = frame.data[i];
        }

        matrix::Matrix<uint8_t, 4, 4> data ({
            {can_id_1, can_id_2, can_id_3, can_id_4},
            {can_data[0], can_data[1], can_data[2], can_data[3]},
            {can_data[4], can_data[5], can_data[6], can_data[7]},
            {frame.can_dlc, 0x0, 0xbe, 0xef}
        });

        return data;
    }

    can_frame matToCan(matrix::Matrix<uint8_t, 4, 4> mat) {
        can_frame frame;
        frame.can_dlc = mat[3][0];

        frame.can_id = mat[0][3];
        frame.can_id <<= 8;
        frame.can_id |= mat[0][2];
        frame.can_id <<= 8;
        frame.can_id |= mat[0][1];
        frame.can_id <<= 8;
        frame.can_id |= mat[0][0];

        for(size_t i = 0; i < frame.can_dlc; i++) {
            size_t row = (i / 4) + 1;
            size_t col = i % 4;
            frame.data[i] = mat[row][col];
        }

        return frame;
    }
};