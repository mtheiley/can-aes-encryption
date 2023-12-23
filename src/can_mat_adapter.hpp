#ifndef CAN_MAT_ADAPTER_H
#define CAN_MAT_ADAPTER_H

#include <cstdint>
#include <linux/can.h>
#include "matrix.hpp"

namespace can_mat_adapter {
    matrix::Matrix<uint8_t, 4, 4> canToMat(can_frame frame);
    can_frame matToCan(matrix::Matrix<uint8_t, 4, 4> mat);
};

#endif //CAN_MAT_ADAPTER_H