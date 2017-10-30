add_subdirectory(uart)
add_subdirectory(delay)

add_library(simulationcore
        ${uart_vt_src}
        ${delay_vt_src}
        )