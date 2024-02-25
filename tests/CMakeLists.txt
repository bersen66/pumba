include(GoogleTest)

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(pumba_tests ${TEST_SOURCES})

target_link_libraries(
    pumba_tests PUBLIC
    pumba
    gtest_main
)

gtest_discover_tests(pumba_tests)
