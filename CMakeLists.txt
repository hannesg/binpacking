cmake_minimum_required (VERSION 2.6)
project(BinPacking)

add_library(linopt
    packing_list.c
)

add_executable(binpacking main.c)
target_link_libraries(binpacking linopt)