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

# Set the target architecture to the Intel Core i7-1065G7
set(CMAKE_CXX_FLAGS "-march=native")
# Enable AVX-512 instructions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f -mavx512cd -mavx512bw -mavx512vl")



# Stack size
MATH(EXPR stack_size "64 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")


#add_executable(sort_quick sort_quick.c)
#add_executable(double_precision double_precision.cpp)

#add_executable(perfect_number perfect_number.c)
add_executable(perfect_number_fast perfect_number_fast.cpp)