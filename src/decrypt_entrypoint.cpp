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
    std::cout << "CAN dest: " << config.canDest() << std::endl;
    std::cout << "Encrypt port: " << config.encryptPort() << std::endl;
    std::cout << "Encrypt host: " << config.encryptHost() << std::endl;

    matrix::Matrix<uint8_t, 4, 4> key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    AES128 aes128(key);

    CanNetwork canOut(config.canDest());
    EncryptNetwork enIn(config.encryptHost(), config.encryptPort());
    enIn.listen();
    
    while(true) {
        steady_clock::time_point begin = steady_clock::now();

        matrix::Matrix<uint8_t, 4, 4> data = enIn.read();
        //std::cout << data << std::endl;
        aes128.decrypt(data);
        //std::cout << data << std::endl;

        can_frame output = can_mat_adapter::matToCan(data);
        //std::cout << std::hex << output.can_id << "[" << (int) output.can_dlc << "] "; 
	    //for (int i = 0; i < output.can_dlc; i++) std::cout << (int) output.data[i] << " ";
	    //std::cout << std::endl;

        canOut.send(output);
        steady_clock::time_point end = steady_clock::now();

        std::cout << "Decrypt Time = " << duration_cast<microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
}