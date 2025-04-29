cmake_minimum_required(VERSION 3.30)
project(silky C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED on)

add_library(silky STATIC src/silky.c)
target_include_directories(silky INTERFACE src)

add_subdirectory(./examples)