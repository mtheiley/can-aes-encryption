#ifndef CAN_NETWORK_H
#define CAN_NETWORK_H

#include <string>
#include <linux/can.h>

class CanNetwork {
public:
    CanNetwork(std::string name);
    can_frame read();
    void send(can_frame frame);
private:
    int socket_;
};

#endif //CAN_NETWORK_H