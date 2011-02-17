set(LIBRARY_SRCS packing_list.c
                 linear_algebra.c
                 first_fit.c
                 approximate_block_solver.c)

add_library(linopt
            SHARED
            ${LIBRARY_SRCS})