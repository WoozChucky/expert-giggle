cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)

link_directories(../model ../common)

add_executable(${PROJECT_NAME} app.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC model common ${Boost_LIBRARIES})