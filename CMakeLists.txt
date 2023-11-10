cmake_minimum_required(VERSION 3.26)
project(Unknown)

set(CMAKE_CXX_STANDARD 23)

add_executable(Unknown main.cpp
        basewin.h
        mainwin.cpp
        mainwin.h
        appcodes.h)

target_link_libraries(Unknown d2d1.lib dwrite.lib)
