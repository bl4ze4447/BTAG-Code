cmake_minimum_required(VERSION 3.24.2)
project(Unknown)
set(CMAKE_CXX_STANDARD 23)
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS -O2)
endif ()

add_executable(Unknown main.cpp
        basewin.h
        mainwin.cpp
        mainwin.h
        appcodes.h)

target_link_libraries(Unknown d2d1.lib dwrite.lib)
