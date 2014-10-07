cmake_minimum_required (VERSION 2.8)
project(QCREADS)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-O3 -static -fopenmp") 
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXE_LINKER_FLAGS "-s")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
include_directories(include)
set(SRC qc.c)
add_executable(raspberry ${SRC})
target_link_libraries(raspberry

m
z
pthread
)

