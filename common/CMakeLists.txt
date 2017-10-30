add_subdirectory(crc)
add_subdirectory(stlm)

add_library(commoncore
        ${crc_src}
        ${stlm_src}
        )
