cmake_minimum_required (VERSION 3.12)
set (CMAKE_C_STANDARD 23)

set (TEST_SOURCES
    "test/test.c"
    "test/test_cont_vec.c")

set (TEST_INCLUDES
    "test/"
    "nami/"
    "./")

project                    (nmtest)
add_executable             (nmtest ${TEST_SOURCES})
target_include_directories (nmtest PRIVATE ${TEST_INCLUDES})