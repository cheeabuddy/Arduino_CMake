option (SIM ON)

if(SIM)
  set(CMAKE_TOOLCHAIN_FILE builds/simulation/SimulationToolchain.cmake) # Simulation Toolchain
else()
  set(CMAKE_TOOLCHAIN_FILE builds/arduino/ArduinoToolchain.cmake) # Arduino Toolchain
endif()

cmake_minimum_required(VERSION 2.8)
project(Root)


#====================================================================#
#  Setup Project                                                     #
#====================================================================#

if(SIM)
  set(CMAKE_CXX_STANDARD 11)
  add_definitions(-D__RISC__)
  include_directories(libsimulationcore)
  add_subdirectory(libsimulationcore)
  include_directories(common)
  add_subdirectory(common)
  add_subdirectory(sim)
else()
  include_directories(libarduinocore)
  add_subdirectory(libarduinocore)
  add_subdirectory(apps)
endif()

