cmake_minimum_required(VERSION 2.6)

find_package(Qt4)
if(QT4_FOUND)
    include(${QT_USE_FILE})

    include_directories(
        "${PROJECT_SOURCE_DIR}/base/include"
        "${PROJECT_SOURCE_DIR}/search/include"
        "${PROJECT_BINARY_DIR}/gui"
        )

    set(PICLEX_SRCS
        main.cpp
        MainWindow.cpp
        SearchModel.cpp
        SearchItem.cpp
        SearchEngineFactory.cpp
#        ImageReadRunnable.cpp
        ImageMapFunc.cpp
        GuiDefines.cpp
        SearchViewDelegate.cpp
        SimpleSearchEngine.cpp
        MockSearchEngine.cpp
        )

    set(PICLEX_MOC_HDRS
        MainWindow.h
        SearchModel.h
        SearchItem.h
#        ImageReadRunnable.h
        SearchViewDelegate.h
        )

    set(PICLEX_UIS
        res/ui/main.ui
        )

    qt4_wrap_cpp(PICLEX_MOC_SRCS ${PICLEX_MOC_HDRS})

    qt4_wrap_ui(PICLEX_UI_HDRS ${PICLEX_UIS})

    add_executable(piclex
        ${PICLEX_SRCS}
        ${PICLEX_MOC_SRCS}
        ${PICLEX_UI_HDRS}
        )

    target_link_libraries(piclex search
        ${QT_LIBRARIES})
else(QT4_FOUND)
    message(WARNING "Qt4 not found - GUI is not available")
endif(QT4_FOUND)
