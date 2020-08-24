cmake_minimum_required(VERSION 3.17)
project(C C)

set(CMAKE_C_STANDARD 11)

add_executable(C main.c
        src/Utils.h
        src/TextPacket.h
    lib src/Variant.h src/TankPacket.h)

target_link_libraries(C ${CMAKE_SOURCE_DIR}/lib/enet64.lib ws2_32.lib winmm.lib)