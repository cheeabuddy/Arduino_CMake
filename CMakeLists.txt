cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(ArduinoCode C CXX)
add_subdirectory(builds)
include_directories(libarduinocore)
add_subdirectory(libarduinocore)
add_subdirectory(blinkLED)
