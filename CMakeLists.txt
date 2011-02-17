cmake_minimum_required (VERSION 2.6)
project(BinPacking)

set(LIBRARY_SRCS packing_list.c
                 linear_algebra.c
                 first_fit.c)

set(TEST_SRCS tests/packing_list.c
              tests/linear_algebra.c
              tests/first_fit.c
              )

set(BINPACKING_SRCS main.c)

add_library(linopt
            SHARED
            ${LIBRARY_SRCS})

add_custom_command(OUTPUT tests.c
    COMMAND ./make-tests.sh ${CMAKE_CURRENT_SOURCE_DIR}/tests > ${CMAKE_CURRENT_BINARY_DIR}/tests.c
    DEPENDS ${TEST_SRCS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(doxygen DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(binpacking ${BINPACKING_SRCS})
target_link_libraries(binpacking linopt)

add_executable(tests tests.c tests/CuTest.c tests/CuTest.h ${TEST_SRCS})
target_link_libraries(tests linopt)
