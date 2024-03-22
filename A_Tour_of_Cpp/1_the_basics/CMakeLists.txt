cmake_minimum_required(VERSION 2.8...3.29.0)
project(1_the_basics VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(1_the_basics main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
