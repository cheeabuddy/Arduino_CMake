add_subdirectory(data_link_layer)
add_subdirectory(application_layer)

set(stlm_src
        ${CMAKE_CURRENT_SOURCE_DIR}/stlm.h
        ${CMAKE_CURRENT_SOURCE_DIR}/data_link_layer/data_link.h
        ${CMAKE_CURRENT_SOURCE_DIR}/data_link_layer/data_link.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application_layer/application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application_layer/application.cpp
        PARENT_SCOPE)