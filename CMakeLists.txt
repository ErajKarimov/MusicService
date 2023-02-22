cmake_minimum_required(VERSION 3.23)
project(SberMusic)

set(CMAKE_CXX_STANDARD 17)

include_directories(Include)

file(GLOB SOURCES
        Include/*.hpp
        Source/*.cpp
        )

add_executable(SberMusic ${SOURCES})

