cmake_minimum_required (VERSION 2.6)
project(BinPacking)

add_library(linopt
            SHARED
            packing_list.c
            linear_algebra.c
)

# FIXME: Test that were added into an existing file won't be executed automatically.
add_custom_command(OUTPUT tests.c
    COMMAND ./make-tests.sh ${CMAKE_CURRENT_SOURCE_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/tests.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

ADD_CUSTOM_TARGET(doxygen DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(binpacking main.c)
target_link_libraries(binpacking linopt)

add_executable(tests tests.c CuTest.c CuTest.h packing_list_test.c linear_algebra_test.c)
target_link_libraries(tests linopt)
