cmake_minimum_required(VERSION 3.27.7)
project(avl VERSION 0.1.0 LANGUAGES C CXX)

add_definitions(-std=c++17)

include(CTest)
enable_testing()

add_executable(avl main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
