cmake_minimum_required (VERSION 2.6)
project(BinPacking)

add_library(linopt
            SHARED
            packing_list.c
)

add_custom_command(OUTPUT tests.c
    COMMAND ./make-tests.sh ${CMAKE_CURRENT_SOURCE_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/tests.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(binpacking main.c)
target_link_libraries(binpacking linopt)

add_executable(tests tests.c CuTest.c CuTest.h packing_list_test.c)
target_link_libraries(tests linopt)
