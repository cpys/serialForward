cmake_minimum_required(VERSION 3.6)
project(serialForward)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(SOURCE_FILES serial.h main.c serial.c)
add_executable(serialForward ${SOURCE_FILES})