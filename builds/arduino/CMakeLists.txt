set(CMAKE_TOOLCHAIN_FILE ArduinoToolchain.cmake) # Arduino Toolchain

set(APP_DIR ../../blinkLED)

#include_directories(APP_DIR)
add_subdirectory(../../blinkLED ${CMAKE_CURRENT_BINARY_DIR}/blinkLED)

set(SOURCE_FILES ../../blinkLED/blinkLED.cc)
message("SOURCE " ${SOURCE_FILES})
add_executable(arduino ${SOURCE_FILES})

set(AVR_HEX)

list(APPEND AVR_HEX
    "-O"
    "ihex"
    "-R"
    ".eeprom"
    "arduino"
    "arduino.hex"
    )

set(AVRDUDE_ARGS)
set(MCU atmega328p)
set(PROTOCOL arduino)
set(UPLOAD_SPEED 115200)
set(PORT /dev/tty.usbmodem1411)

list(APPEND AVRDUDE_ARGS
    "-p" "${MCU}"
    "-c" "${PROTOCOL}"
    "-b" "${UPLOAD_SPEED}"       # Baud rate
    "-P" "${PORT}"               # Serial port
    "-D"                         # Dont erase
    "-U" "flash:w:arduino.hex"
    )


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

add_custom_target(bin2hex
                    avr-objcopy
                    ${AVR_HEX}
                    COMMENT "Generating HEX image"
                    VERBATIM
                    )

add_custom_target(upload
                  avrdude
                  ${AVRDUDE_ARGS}
                  COMMENT "Uploading to target"
                  VERBATIM
                  )
