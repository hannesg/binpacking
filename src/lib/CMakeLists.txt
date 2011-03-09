set(LIBRARY_SRCS packing_list.c
                 linear_algebra.c
                 first_fit.c
                 approximate_block_solver.c
                 binpacking.c
                 approximate_lp_solver.c
                 approximate_max_min_resource_sharing.c
                 )


add_library(linopt
            SHARED
            ${LIBRARY_SRCS})
            
target_link_libraries(linopt m)