cmake_minimum_required(VERSION 3.5)

project(yanbtedit LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(libyanbt)

set(PROJECT_SOURCES
        main.cpp
        main_window.cpp
		nbt_tree_view.h
		nbt_tree_view.cpp
        main_window.h
        main_window.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(yanbtedit
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(yanbtedit SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(yanbtedit
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(yanbtedit PRIVATE nbtfile nbtread nbttag Qt${QT_VERSION_MAJOR}::Widgets)
