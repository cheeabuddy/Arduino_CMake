#
# Arduino Build system
#

set(CMAKE_SYSTEM_NAME Generic)


set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# Add current directory to CMake Module path automatically
if(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/Platform/Arduino.cmake)
    set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
endif()

set(CSTANDARD "-std=gnu99")
set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CINCS "-I${ArduinoCode_SOURCE_DIR}/libarduinocore")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000")


set(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CSTANDARD} ${CEXTRA}")
set(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")

#set(CMAKE_C_FLAGS
#            "-mmcu=atmega328p"
#            "-gstabs"
#            "-DF_CPU=16000000"
#            "-I/libarduinocore"
#            "-Os"
#            "-Wall -Wstrict-prototypes"
#            )

#set(CMAKE_CXX_FLAGS
#          "-mmcu=atmega328p"
#          "-DF_CPU=16000000"
#          "-I/libarduinocore"
#          "-Os"
#          )

set(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "")
set(CMAKE_CXX_FLAGS ${CXXFLAGS} CACHE STRING "")

#message("C_" ${CMAKE_C_FLAGS})
#message("CXX_" ${CMAKE_CXX_FLAGS})
