cmake_minimum_required(VERSION 3.16)

project(guided_optimization
  LANGUAGES C
  DESCRIPTION "OMP Example")

find_package(OpenMP REQUIRED)

add_executable(try try.c)
target_link_libraries(try
  PUBLIC
  OpenMP::OpenMP_C)
