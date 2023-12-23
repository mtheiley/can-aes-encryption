#include <cstring>
#include <stdexcept>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "can_network.hpp"

CanNetwork::CanNetwork(std::string name) {
    socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(socket_ < 0) throw std::runtime_error("failed to create socket");
    
    ifreq ifr;
    strcpy(ifr.ifr_name, name.c_str());
    int ioctl_ = ioctl(socket_, SIOCGIFINDEX, &ifr);

    if(ioctl_ < 0) throw std::runtime_error("failed to manipulate network interface");

    sockaddr_can addr;
	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    int bind_ = bind(socket_, (sockaddr* ) &addr, sizeof(addr));

    if(bind_ < 0) throw std::runtime_error("failed to bind socket");
}

can_frame CanNetwork::read() {
    can_frame frame;
    int nbytes = ::read(socket_, &frame, sizeof(struct can_frame));

    if (nbytes < 0) throw std::runtime_error("failed to read socket");
    return frame;
}

void CanNetwork::send(can_frame frame) {
    int nbytes = write(socket_, &frame, sizeof(struct can_frame));

    if(nbytes != sizeof(can_frame)) throw std::runtime_error("failed to write bytes");
}
