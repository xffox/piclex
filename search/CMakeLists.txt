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
    "src/TreeBuilderParser.cpp"
    "src/ParseNode.cpp"
    "src/IndexToken.cpp"
    "src/InvertedIndex.cpp"
    "src/IndexMaker.cpp"
    "src/IndexSearcher.cpp"
    "src/FsDocProvider.cpp"
    "src/DocIdReader.cpp"
    "src/Searcher.cpp"
    "src/IndexMakerFactory.cpp"
    "src/IndexSearcherFactory.cpp"
    "src/DocDescription.cpp"
    "src/ImageDocProcessor.cpp"
    "src/SubsentenceGatherer.cpp"
    "src/DocDescriptionGatherer.cpp"
    "src/ImageDocDescription.cpp"

    "src/mock/WordDocProcessor.cpp"
    "src/mock/SimpleIndexMaker.cpp"
    "src/mock/SimpleIndexSearcher.cpp"
    "src/mock/SimpleDocProvider.cpp"
    )

target_link_libraries(search base)

add_subdirectory(tests)
