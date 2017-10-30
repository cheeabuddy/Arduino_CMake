#
# Simulation Build system
#

set(CMAKE_SYSTEM_NAME Generic)
set(Root_SOURCE_DIR)

set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)

set(CSTANDARD "-std=gnu99")
set(CWARN "-Wall -Wstrict-prototypes")
set(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
set(COPT "-Os")
set(CINCS "-I${Root_SOURCE_DIR}/libsimulationcore")


set(CFLAGS "${CINCS} ${CWARN}")
set(CXXFLAGS "${CINCS} -Wc++11-extensions")


set(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "")
set(CMAKE_CXX_FLAGS ${CXXFLAGS} CACHE STRING "")
