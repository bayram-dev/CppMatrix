cmake_minimum_required(VERSION 3.19)
project(lab02)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(lab02
        main.cpp
        matrix.cpp
        matrix.h
        input.txt)
