cmake_minimum_required(VERSION 3.20)
project(RTOS_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(RTOS-simulator 
    src/main.cpp
)
