cmake_minimum_required(VERSION 3.17)
project(unp C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/local/include)

add_executable(unp main.c cp1/get_time_tcp.c)