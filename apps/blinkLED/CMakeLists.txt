#====================================================================#
#  Setup App                                                         #
#====================================================================#
project(blinkLED C CXX)


include_directories(/libarduinocore)
link_directories(/libarduinocore)

link_libraries(arduinocore)


set(SOURCE_FILES blinkLED.cc)
add_executable(blinkLED.bin ${SOURCE_FILES})