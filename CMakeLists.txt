cmake_minimum_required(VERSION 3.17)
project(C C)

set(CMAKE_C_STANDARD 11)

add_executable(C main.c
    src/utils.h
    src/GamePacket.h
    lib)

target_link_libraries(C ${CMAKE_SOURCE_DIR}/lib/enet64.lib ws2_32.lib winmm.lib)