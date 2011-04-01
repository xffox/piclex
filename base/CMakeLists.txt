cmake_minimum_required(VERSION 2.6)

include_directories("include")

add_library(base STATIC
    "src/Logger.cpp"
    "src/Mutex.cpp"
    )
