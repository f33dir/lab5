cmake_minimum_required(VERSION 3.8)
project(lab5)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
LINK_DIRECTORIES(bass/x64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bass)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib/toolkit
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib/ape
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib/mpeg
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib/mpeg/id3v1
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/taglib/mpeg/id3v2
  ${CMAKE_CURRENT_SOURCE_DIR}/taglib/bindings/c/
)
link_libraries(stdc++fs)
add_executable(${PROJECT_NAME} "main.cpp"
                               "mp3manager.cpp" "mp3manager.h"
                               "song.h" "song.cpp"
                               "mp3filemanager.h" "mp3filemanager.cpp" "bass/bass.h"
                               "mp3player.h" "mp3player.cpp"
                               "mainwindow.ui" "mainwindow.h" "mainwindow.cpp")
add_subdirectory(taglib/taglib taglib/bindings)
target_link_libraries(lab5 tag)
TARGET_LINK_LIBRARIES(lab5 bass)
target_link_libraries(lab5 Qt5::Widgets)
