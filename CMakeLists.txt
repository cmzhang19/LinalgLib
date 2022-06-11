cmake_minimum_required(VERSION 3.0)

project(LinearAlgebraLib)

Set(CXX_STANDARD_REQUIRED 11)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

add_subdirectory(src)
add_subdirectory(tests)