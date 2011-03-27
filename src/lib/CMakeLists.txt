set(LIBRARY_SRCS double_matrix.c
                 double_vector.c
                 uint_matrix.c
                 uint_vector.c
                 mixed_vector.c
                 print_double_array.c
                 print_uint_array.c

                 packing_list.c
                 first_fit.c
                 approximate_block_solver.c
                 binpacking.c
                 approximate_lp_solver.c
                 approximate_max_min_resource_sharing.c
                 
                 knapsack.c
                 )


add_library(linopt
            SHARED
            ${LIBRARY_SRCS})
            
target_link_libraries(linopt m)