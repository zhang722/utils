cmake_minimum_required(VERSION 3.0)
project(vscode_cmake_Test)

include_directories(./include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")
add_executable(${PROJECT_NAME} main.cpp)
