set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain
message("TOOL_" ${CMAKE_TOOLCHAIN_FILE})

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(ArduinoCode C CXX)

include_directories(libarduinocore)

add_subdirectory(libarduinocore)
add_subdirectory(blinkLED)
