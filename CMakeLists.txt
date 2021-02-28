cmake_minimum_required(VERSION 3.17)
project(project_one)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(project_one
        include/BackChain.hpp
        include/ClauseItem.hpp
        include/KnowledgeBase.hpp
        include/Statement.hpp
        include/VariableListItem.hpp
        include/ForwardChain.hpp
        src/Project1-bss64-dat54-rrh93.cpp.cpp
        src/BackChain.cpp
        src/ClauseItem.cpp
        src/KnowledgeBase.cpp
        src/Statement.cpp
        src/VariableListItem.cpp
        src/ForwardChain.cpp)