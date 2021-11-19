cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(dummy_plugin C)

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads REQUIRED)

find_package(PkgConfig)

pkg_check_modules(GSTREAMER REQUIRED
    gstreamer-1.0>=1.4
    gstreamer-video-1.0
    gstreamer-app-1.0
    gstreamer-allocators-1.0
    glib-2.0)

link_directories(${GSTREAMER_LIBRARY_DIRS})

file(GLOB DUMMY_SOURCES *.c)
file(GLOB DUMMY_HEADERS *.h)

   add_library(dummy SHARED
 ${DUMMY_SOURCES}
  ${DUMMY_HEADERS})


target_link_libraries(dummy ${CMAKE_DL_LIBS} Threads::Threads rt ${GSTREAMER_LIBRARIES} cairo)

target_include_directories(dummy PRIVATE ${GSTREAMER_INCLUDE_DIRS})

