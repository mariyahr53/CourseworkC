cmake_minimum_required(VERSION 4.0)
project(CourseWork1)

set(CMAKE_CXX_STANDARD 20)

add_executable(CourseWork1 main.cpp
        Module.cpp
        Module.h
        Grade.cpp
        Grade.h
        Transcript.cpp
        Transcript.h)
