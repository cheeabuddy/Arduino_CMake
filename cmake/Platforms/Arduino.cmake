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


set(CMAKE_C_FLAGS  ${CFLAGS} CACHE)
set(CMAKE_CXX_FLAGS ${CXXFLAGS} CACHE)
