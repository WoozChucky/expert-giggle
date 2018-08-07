cmake_minimum_required(VERSION 3.10)
project(model)

set(CMAKE_CXX_STANDARD 17)

add_library(model SHARED user.h Entity.cpp Entity.h)

target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})