cmake_minimum_required(VERSION 3.17)
project(project_one)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(project_one
        include/mainwindow.h
        include/mainwindow.h
        include/BackChain.h
        include/ClauseItem.h
        include/KnowledgeBase.h
        include/Statement.h
        include/VariableListItem.h
        include/ForwardChain.h
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.cpp
        src/BackChain.cpp
        src/ClauseItem.cpp
        src/KnowledgeBase.cpp
        src/Statement.cpp
        src/VariableListItem.cpp
        src/ForwardChain.cpp)