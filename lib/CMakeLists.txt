include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(
    SOURCES
    src/pumba.cpp
)
add_library(pumba ${SOURCES})

target_include_directories(
    pumba
    INTERFACE $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/include>
)
