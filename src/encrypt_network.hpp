#ifndef ENCRYPT_NETWORK_H
#define ENCRYPT_NETWORK_H

#include <string>
#include <cstdint>
#include <netinet/in.h>
#include "matrix.hpp"

class EncryptNetwork {
public:
    EncryptNetwork(std::string host, uint16_t port);
    void listen();
    matrix::Matrix<uint8_t, 4, 4> read();
    void send(matrix::Matrix<uint8_t, 4, 4> data);
private:
    int socket_;
    sockaddr_in addr;
};

#endif //ENCRYPT_NETWORK_H