# About
This project allows encryption and decryption of CAN messages by using sockets.

# Running
There are two executables that are created from this program. A CAN encrypter and a CAN decrypter.
`./can_encrypt`
`./can_decrypt` 

# Building
`cmake -G Ninja ..`
`ninja`

# Debug Build
`cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..`
`ninja`

# Run Tests
`ctests`
