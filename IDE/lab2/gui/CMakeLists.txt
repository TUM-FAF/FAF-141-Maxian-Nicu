cmake_minimum_required(VERSION 3.3)
project(calc-gui)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
    main.cpp Solver.cpp Solver.h)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

add_executable(calc-gui ${SOURCE_FILES})

target_link_libraries(calc-gui
        ${GTKMM_LIBRARIES}  )
