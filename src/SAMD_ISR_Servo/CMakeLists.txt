cmake_minimum_required(VERSION 3.10)
project("SAMD_ISR_Servo" VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(samdisr SAMD_ISR_Servo.cpp SAMD_FastTimerInterrupt.cpp)
target_link_arduino_libraries(samdisr PRIVATE core)