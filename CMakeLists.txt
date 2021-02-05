cmake_minimum_required(VERSION 3.17)
project(project_one)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(project_one
        include/mainwindow.h
        src/main.cpp
        src/mainwindow.cpp)
