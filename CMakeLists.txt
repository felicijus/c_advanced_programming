cmake_minimum_required(VERSION 3.24)
project(c_advanced_programming  C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# added -fopenmp
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


# Stack size
MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(sort_quick sort_quick.c)
#add_executable(double_precision double_precision.cpp)
