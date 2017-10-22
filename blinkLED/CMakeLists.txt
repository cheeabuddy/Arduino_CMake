
include_directories(/libarduinocore)
link_directories(/libarduinocore)

link_libraries(arduinocore)

#set(TARGET_PGRM blinkLED)

set(SOURCE_FILES blinkLED.cc CACHE STRING "")
