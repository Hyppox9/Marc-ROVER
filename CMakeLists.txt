cmake_minimum_required(VERSION 3.28)
project(Marc_ROVER C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Marc_ROVER
        main.c
        timer.c
        timer.h)
