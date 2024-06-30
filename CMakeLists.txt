cmake_minimum_required(VERSION 3.28)
project(BrainFuck)

set(CMAKE_CXX_STANDARD 23)

add_executable(bf_hello_world hello_world.cpp
        Command.h
        Compiler.h)
