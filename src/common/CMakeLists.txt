cmake_minimum_required(VERSION 3.10)
project(common)

set(CMAKE_CXX_STANDARD 17)
set(EXTERNAL_LIB_INCLUDE ../../include)

find_package(Boost 1.67 COMPONENTS system filesystem REQUIRED)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()

if(Boost_FOUND)
    message(STATUS "Boost was found!")
    message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
    message(STATUS "Boost Include Dir: ${Boost_INCLUDE_DIR}")
    message(STATUS "Current src Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

add_library(${PROJECT_NAME} SHARED Subject.hpp Temporary.cpp threading/ThreadSafeQueue.hpp threading/ThreadPool.hpp logging/Logger.hpp memory/MemoryPool.cpp memory/MemoryPool.hpp exceptions/Exception.cpp exceptions/Exception.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${EXTERNAL_LIB_INCLUDE})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})