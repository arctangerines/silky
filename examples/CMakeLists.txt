cmake_minimum_required(VERSION 3.30)
project(silkyexample C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(silkyex silkyex1.c)

target_link_libraries(silkyex silky)
