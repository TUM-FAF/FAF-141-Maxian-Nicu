cmake_minimum_required(VERSION 3.3)
project(wp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Widget.cpp Widget.h Button.cpp Button.h TextEdit.cpp TextEdit.h TextWidget.cpp TextWidget.h Label.cpp Label.h ListBox.cpp ListBox.h ScrollBar.cpp ScrollBar.h)
add_executable(wp2 ${SOURCE_FILES})