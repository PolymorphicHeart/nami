cmake_minimum_required (VERSION 3.12)
set (CMAKE_C_STANDARD 23)

set (NAMI_SOURCES
    "nami/src/darwin_memory.c")

set (NAMI_INCLUDES
    "nami/include"
    "nami/")

if (APPLE)
    set (NAMI_LIBS "System")
endif (APPLE)

project                    (nami)
add_library                (nami SHARED ${NAMI_SOURCES})
target_include_directories (nami PRIVATE ${NAMI_INCLUDES})
target_link_options        (nami PRIVATE -nostdlib)
target_link_libraries      (nami ${NAMI_LIBS})

set (TEST_SOURCES
    "test/test.c")

set (TEST_INCLUDES
    "test/"
    "nami/include"
    "./")

project                    (nmtest)
add_executable             (nmtest ${TEST_SOURCES})
target_include_directories (nmtest PRIVATE ${TEST_INCLUDES})
target_link_options        (nmtest PRIVATE -nostdlib)
target_link_libraries      (nmtest nami)