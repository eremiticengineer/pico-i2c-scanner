set(PROJECT picoi2cscanner)

cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2 CACHE STRING "Board type")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()

add_executable(${PROJECT}
  src/pico-i2c-scanner.cpp
)

target_link_libraries(${PROJECT}
  pico_stdlib
  hardware_i2c
)

pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 1)

pico_add_extra_outputs(${PROJECT})
