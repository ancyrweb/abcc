cmake_minimum_required(VERSION 3.24)
project(abcc)

set(CMAKE_CXX_STANDARD 14)

add_executable(abcc src/main.cpp src/Parser.cpp src/Parser.h src/Lexer.cpp src/Lexer.h src/Compiler.cpp src/Compiler.h)
