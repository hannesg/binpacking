set(TEST_SRCS test_packing_list.c
              test_linear_algebra.c
              test_first_fit.c
              test_approximate_block_solver.c
              test_approximate_lp_solver.c
              test_approximate_max_min_resource_sharing.c
              test_binpacking.c
              test_knapsack.c
              )

add_custom_command(OUTPUT tests.c
    COMMAND ./make-tests.sh > ${CMAKE_CURRENT_BINARY_DIR}/tests.c
    DEPENDS ${TEST_SRCS} ./make-tests.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(tests tests.c CuTest.c CuTest.h ${TEST_SRCS})
target_link_libraries(tests linopt)