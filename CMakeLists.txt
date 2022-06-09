cmake_minimum_required(VERSION 3.0)

project(LinearAlgebraLib)

Set(CXX_STANDARD_REQUIRED 11)

add_executable(main main.cpp Vector.cpp Vector.h Matrix.cpp Matrix.h)
