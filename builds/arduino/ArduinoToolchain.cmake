#
# Arduino Build system
#

set(CMAKE_SYSTEM_NAME Generic)
set(Root_SOURCE_DIR)


set(CMAKE_C_COMPILER   avr-gcc CACHE STRING "")
set(CMAKE_CXX_COMPILER avr-g++ CACHE STRING "")


set(CSTANDARD "-std=gnu99")
set(CDEBUG "-gstabs")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CINCS "-I${Root_SOURCE_DIR}/libarduinocore")
set(CMCU "-mmcu=atmega328p")
set(CDEFS "-DF_CPU=16000000")


set(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CSTANDARD} ${CEXTRA}")
set(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")


set(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "")
set(CMAKE_CXX_FLAGS ${CXXFLAGS} CACHE STRING "")


