cmake_minimum_required(VERSION 3.31)
project(YLang)

set(CMAKE_CXX_STANDARD 26)

add_executable(YLang src/main.cpp
        src/ast.cpp
        src/ast.h
        src/Tokenization.cpp
        src/Tokenization.h)