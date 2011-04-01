cmake_minimum_required(VERSION 2.6)

include_directories(
    "${PROJECT_SOURCE_DIR}/base/include"
    "${PROJECT_SOURCE_DIR}/graphics/include"
    )

add_executable(tester tester.cpp)
target_link_libraries(tester graphics base)
