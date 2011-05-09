cmake_minimum_required(VERSION 2.6)

include_directories("include"
    "${PROJECT_SOURCE_DIR}/base/include"
    )

add_library(search STATIC
    "src/Symbol.cpp"
    "src/Sentence.cpp"
    "src/Rule.cpp"
    "src/Grammar.cpp"
    "src/Parser.cpp"
    "src/ParserInstance.cpp"
    "src/TreeBuilderParserInstance.cpp"
    "src/ParseNode.cpp"
    "src/IdStorage.cpp"
    "src/IndexToken.cpp"
    "src/InvertedIndex.cpp"
    )

target_link_libraries(search base)

add_subdirectory(tests)
