set(CMAKE_TOOLCHAIN_FILE SimulationToolchain.cmake) # Simulation Toolchain

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(SimulationCode C CXX)


add_definitions(-D__RISC__)
set(SOURCE_FILES main.cpp)

add_executable(simulation ${SOURCE_FILES})
