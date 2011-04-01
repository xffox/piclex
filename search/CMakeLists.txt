cmake_minimum_required(VERSION 2.6)

include_directories("include")

add_library(search STATIC
    "src/Symbol.cpp"
    "src/Sentence.cpp"
    )

add_subdirectory(tests)
