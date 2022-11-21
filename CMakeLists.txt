cmake_minimum_required(VERSION 3.10)
project("HighROV-MATE" VERSION 0.7)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/SAMD_ISR_Servo/)

add_executable(main HighROV.cpp Crc.cpp Data.cpp AnalogSensors.cpp DepthSensor.cpp Manipulator.cpp IMUSensor.cpp RotaryCameras.cpp Networking.cpp Thrusters.cpp Debug.cpp PWMController.cpp)
target_compile_definitions(main PRIVATE __SOFTFP__=1)
target_link_libraries(main PUBLIC samdisr)
target_link_arduino_libraries(main PRIVATE Wire core SparkFun_PCA9536_Arduino_Library Servo  SPI Ethernet MS5837)
target_enable_arduino_upload(main)