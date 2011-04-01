cmake_minimum_required(VERSION 2.6)

project(piclex)

enable_testing()

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

set(WARN_FLAGS "-Wall -Wextra")
set(DEBUG_FLAGS "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${DEBUG_FLAGS}")

add_subdirectory(base)
add_subdirectory(graphics)
add_subdirectory(search)
add_subdirectory(tester)
