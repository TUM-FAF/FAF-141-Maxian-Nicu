cmake_minimum_required(VERSION 3.3)
project(wp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Widget.cpp Widget.h Button.cpp Button.h TextEdit.cpp TextEdit.h TextWidget.cpp TextWidget.h Label.cpp Label.h)
add_executable(wp1 ${SOURCE_FILES})