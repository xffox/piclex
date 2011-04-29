cmake_minimum_required(VERSION 2.6)
include(FindPkgConfig)

pkg_search_module(CPPUNIT cppunit)
if(CPPUNIT_FOUND)
    include_directories(${CPPUNIT_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/search/include")

    add_executable(search_test test.cpp
        SymbolTest.cpp
        ParserTest.cpp
        TreeTest.cpp
        )
    target_link_libraries(search_test ${CPPUNIT_LIBRARIES} search)

    add_test(SearchTest "${EXECUTABLE_OUTPUT_PATH}/search_test")
#TODO: message
endif(CPPUNIT_FOUND)
