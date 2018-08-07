cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 17)
set(LIB_MODEL_SRC ../model)

link_directories(../model)

#add_library(model SHARED ${LIB_MODEL_SRC})

#find_library(MODEL_LIBRARY model HINTS ../model)

add_executable(${PROJECT_NAME} app.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC model)