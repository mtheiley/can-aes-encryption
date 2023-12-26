#include <iostream>
#include <cstdint>
#include <chrono>

#include "matrix.hpp"
#include "aes128.hpp"
#include "can_network.hpp"
#include "can_mat_adapter.hpp"
#include "encrypt_network.hpp"
#include "config.hpp"

using namespace std::chrono;

int main() {
    
    Config& config = Config::getConfig();
    std::cout << "CAN source: " << config.canSource() << std::endl;
    std::cout << "Encrypt port: " << config.encryptPort() << std::endl;
    std::cout << "Encrypt host: " << config.encryptHost() << std::endl;

    matrix::Matrix<uint8_t, 4, 4> key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    AES128 aes128(key);

    CanNetwork canIn(config.canSource());
    EncryptNetwork enOut(config.encryptHost(), config.encryptPort());

    while(true) {
        steady_clock::time_point begin = steady_clock::now();
        can_frame frame = canIn.read();
        //std::cout << std::hex << frame.can_id << "[" << (int) frame.can_dlc << "] "; 
	    //for (int i = 0; i < frame.can_dlc; i++) std::cout << (int) frame.data[i] << " ";
	    //std::cout << std::endl;

        matrix::Matrix data = can_mat_adapter::canToMat(frame);

        //std::cout << data << std::endl;
        aes128.encrypt(data);

        enOut.send(data);
        steady_clock::time_point end = steady_clock::now();

        std::cout << "Encrypt Time = " << duration_cast<microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
}