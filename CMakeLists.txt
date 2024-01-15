cmake_minimum_required (VERSION 3.12)
set (CMAKE_C_STANDARD 23)

set (NAMI_SOURCES
    "nami/strings.c")

set (NAMI_INCLUDES
    "nami/include"
    "nami/")

project                    (nami)
add_library                (nami STATIC ${NAMI_SOURCES})
target_include_directories (nami PRIVATE ${NAMI_INCLUDES})

set (TEST_SOURCES
    "test/test.c")

set (TEST_INCLUDES
    "test/"
    "nami/"
    "./")

project                    (nmtest)
add_executable             (nmtest ${TEST_SOURCES})
target_include_directories (nmtest PRIVATE ${TEST_INCLUDES})
target_link_libraries      (nmtest nami)