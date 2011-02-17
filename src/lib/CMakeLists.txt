set(LIBRARY_SRCS packing_list.c
                 linear_algebra.c
                 first_fit.c
                 approximate_block_solver.c
                 binpacking.c
                 )


add_library(linopt
            SHARED
            ${LIBRARY_SRCS})
            
target_link_libraries(linopt m)