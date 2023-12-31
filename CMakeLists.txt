cmake_minimum_required(VERSION 3.27)
project(can_aes_encryption)

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
set(CMAKE_CXX_COMPILER      "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS         "-Wpedantic")

include(CTest)
set(CMAKE_CXX_STANDARD 20)

# Add googletest package
add_subdirectory(packages/googletest)
add_subdirectory(packages/yaml-cpp)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(packages/yaml-cpp/include)

add_library(can_aes_lib
    src/config.cpp
    src/can_mat_adapter.cpp
    src/can_network.cpp
    src/encrypt_network.cpp
    src/galoistable.cpp
    src/sub_box.cpp
)

add_executable(can_encrypt
    src/encrypt_entrypoint.cpp
)

add_executable(can_decrypt
    src/decrypt_entrypoint.cpp
)

add_executable(unit_test
    test/example_test.cpp
)

target_link_libraries(can_encrypt
    can_aes_lib
    yaml-cpp
)

target_link_libraries(can_decrypt
    can_aes_lib
    yaml-cpp
)

target_link_libraries(unit_test
    gtest
    gtest_main
    can_aes_lib
)

add_test(memory_test can_aes)
add_test(unit_test unit_test)

add_custom_target(memtest
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND ${CMAKE_COMMAND} -E cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

add_custom_target(get_packages
    COMMAND echo "Getting Packages..."
    COMMAND mkdir ../packages || (exit 0)
    COMMAND git clone https://github.com/google/googletest/ ../packages/googletest || (exit 0)
    COMMAND git clone https://github.com/jbeder/yaml-cpp.git ../packages/yaml-cpp || (exit 0)
)