#include <iostream>
#include <cstdint>
#include "matrix.hpp"
#include "aes128.hpp"
#include "can_network.hpp"
#include "can_mat_adapter.hpp"
#include "encrypt_network.hpp"

int main() {
    
    matrix::Matrix<uint8_t, 4, 4> key ({
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}
    });

    AES128 aes128(key);

    CanNetwork canOut("vcan1");
    EncryptNetwork enIn("192.168.1.13", 2115);
    enIn.listen();
    
    while(true) {
        matrix::Matrix<uint8_t, 4, 4> data = enIn.read();
        std::cout << data << std::endl;
        aes128.decrypt(data);
        std::cout << data << std::endl;

        can_frame output = can_mat_adapter::matToCan(data);
        std::cout << std::hex << output.can_id << "[" << (int) output.can_dlc << "] "; 
	    for (int i = 0; i < output.can_dlc; i++) std::cout << (int) output.data[i] << " ";
	    std::cout << std::endl;

        canOut.send(output);
    }
}