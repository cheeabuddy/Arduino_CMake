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

add_custom_command(TARGET blinkLED POST_BUILD
                    avr-objcopy
                    ${AVR_HEX}
                    COMMENT "Generating HEX image"
                    VERBATIM
                    )


add_custom_command(TARGET blinkLED POST_BUILD
                  avrdude
                  ${AVRDUDE_ARGS}
                  COMMENT "Uploading to target"
                  VERBATIM
                  )
