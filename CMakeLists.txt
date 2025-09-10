cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled main.cpp
        Point.cpp
        Point.h
        Matrix.cpp
        Matrix.h
        FileHandler.cpp
        FileHandler.h
)
