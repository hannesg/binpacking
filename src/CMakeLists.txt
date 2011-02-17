add_subdirectory(lib)

set(BINPACKING_SRCS main.c)

add_executable(binpacking ${BINPACKING_SRCS}) 
target_link_libraries(binpacking linopt)
