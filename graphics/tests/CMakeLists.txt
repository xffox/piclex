cmake_minimum_required(VERSION 2.6)
include(FindPkgConfig)

pkg_search_module(CPPUNIT cppunit)
if(CPPUNIT_FOUND)
    include_directories(${CPPUNIT_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/graphics/include")

    add_executable(graphics_test test.cpp ImageTest.cpp)
    target_link_libraries(graphics_test ${CPPUNIT_LIBRARIES} graphics)

    add_test(GraphicsTest "${EXECUTABLE_OUTPUT_PATH}/graphics_test")
endif(CPPUNIT_FOUND)
