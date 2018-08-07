cmake_minimum_required(VERSION 3.10)
project(dal)

set(CMAKE_CXX_STANDARD 17)

add_library(dal SHARED library.cpp library.h)