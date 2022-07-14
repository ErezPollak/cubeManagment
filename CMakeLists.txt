cmake_minimum_required(VERSION 3.21)
project(cubeManagment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cubeManagment
        Cube.cpp
        Cube.h
        DataBase.cpp
        DataBase.h
        main.cpp
        tests.cpp)
