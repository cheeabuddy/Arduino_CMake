
include_directories(/libarduinocore)
link_directories(/libarduinocore)

link_libraries(arduinocore)

#set(TARGET_PGRM blinkLED)
add_executable(blinkLED blinkLED.cc)

set(AVR_HEX)

list(APPEND AVR_HEX
    "-O"
    "ihex"
    "-R"
    ".eeprom"
    "blinkLED"
    "blinkLED.hex"
    )

set(AVRDUDE_ARGS)
set(MCU atmega328p)
set(PROTOCOL arduino)
set(UPLOAD_SPEED 115200)
set(PORT /dev/tty.usbmodem1411)

list(APPEND AVRDUDE_ARGS
    "-p" "${MCU}"
    "-c" "${PROTOCOL}"
    "-b" "${UPLOAD_SPEED}"     # Baud rate
    "-P" "${PORT}"                         # Serial port
    "-D"                                # Dont erase
    "-U" "flash:w:blinkLED.hex"
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
