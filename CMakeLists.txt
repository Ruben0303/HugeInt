project(HugeInt)
cmake_minimum_required(VERSION 3.7)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(hugeint test_run/TEST.cpp lib/huge_int.cpp)
