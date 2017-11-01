cmake_minimum_required(VERSION 3.8)
project(GetArx)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES getArx.cpp sha1.cpp)
add_executable(GetArx ${SOURCE_FILES})