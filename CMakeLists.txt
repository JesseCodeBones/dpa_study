cmake_minimum_required(VERSION 3.0.0)
project(dpa_study VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()

add_executable(dpa_study main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
