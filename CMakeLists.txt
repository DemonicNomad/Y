cmake_minimum_required(VERSION 3.31)
project(YLang)

set(CMAKE_CXX_STANDARD 26)

add_executable(YLang src/main.cpp
        src/ast.cpp
        src/ast.h
        src/Lexer.cpp
        src/Lexer.h
        src/Token.h
        src/Generation.cpp
        src/Generation.h
        src/Nodes.h)