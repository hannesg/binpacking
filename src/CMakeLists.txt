add_subdirectory(lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(tests)

set(BINPACKING_SRCS main.c
                    parse_instance.c)

add_executable(binpacking ${BINPACKING_SRCS}) 
target_link_libraries(binpacking linopt)
