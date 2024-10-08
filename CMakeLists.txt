cmake_minimum_required(VERSION 3.29)
project(Assignment2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Assignment2
        check_mm.c
        io.c
        io.h
        main.c
        memory_setup.c
        mm.c
        mm.h
        mm_aux.c)


