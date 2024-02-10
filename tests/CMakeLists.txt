include(GoogleTest)

set(

    TESTS_SOURCES
    everything_work.cpp
)

add_executable(pumba_tests ${TESTS_SOURCES})

target_link_libraries(
    pumba_tests PUBLIC
    pumba
    gtest_main
)

gtest_discover_tests(pumba_tests)
