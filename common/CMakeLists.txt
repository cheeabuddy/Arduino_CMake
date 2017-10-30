add_subdirectory(crc)
add_subdirectory(stlm)


include_directories(/libsimulationcore)
link_directories(/libsimulationcore)
link_libraries(simulationcore)

add_library(commoncore
        ${crc_src}
        ${stlm_src}
        )
