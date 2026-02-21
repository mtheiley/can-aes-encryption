cmake_minimum_required(VERSION 3.27)
project(can_aes_encryption)

set(CMAKE_CXX_COMPILER      "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS         "-Wpedantic")

set(CMAKE_CXX_STANDARD 20)

add_executable(aes_main
    src/main.cpp
)