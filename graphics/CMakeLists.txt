cmake_minimum_required(VERSION 2.6)

include_directories("include")

add_library(graphics STATIC "src/Image.cpp")

add_subdirectory(tests)
