#====================================================================#
#  Setup Simulation                                                    #
#====================================================================#
project(SimulationCode C CXX)
add_definitions(-D__RISC__)

include_directories(/libsimulationcore)
link_directories(/libsimulationcore)

link_libraries(simulationcore)

include_directories(/common)
link_directories(/common)

link_libraries(commoncore)
target_link_libraries(commoncore simulationcore)


set(SOURCE_FILES main.cpp)

add_executable(simulation.bin ${SOURCE_FILES})
target_link_libraries(simulation.bin simulationcore commoncore)