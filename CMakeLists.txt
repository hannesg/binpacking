cmake_minimum_required (VERSION 2.6)
project(BinPacking)

add_subdirectory(src)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(doxygen
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${TEST_SRCS} ${BINPACKING_SRCS} ${LIBRARY_SRCS}
    COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

