#include <stdexcept>
#include <unistd.h>

#include <arpa/inet.h> // htons, inet_add

#include "encrypt_network.hpp"

EncryptNetwork::EncryptNetwork(std::string host, uint16_t port) {
	socket_ = socket(AF_INET, SOCK_DGRAM, 0);
	
    if (socket_ < 0) throw std::runtime_error("failed to create encrypt socket");

	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
}

void EncryptNetwork::listen() {
    int bind_ = bind(socket_, (sockaddr *)&addr, sizeof(addr));
	
    if(bind_ < 0) throw std::runtime_error("failed to bind encrypt socket");
}

matrix::Matrix<uint8_t, 4, 4> EncryptNetwork::read() {
    matrix::Matrix<uint8_t, 4, 4> data;
	int nbytes = ::read(socket_, &data, sizeof(matrix::Matrix<uint8_t, 4, 4>));

    if(nbytes < 0) throw std::runtime_error("failed to read encrypted bytes");
    return data;
}

void EncryptNetwork::send(matrix::Matrix<uint8_t, 4, 4> data) {
    int nbytes = ::sendto(socket_, &data, sizeof(matrix::Matrix<uint8_t, 4, 4>),
     0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    if(nbytes < 0) throw std::runtime_error("failed to write encrypted bytes");
}