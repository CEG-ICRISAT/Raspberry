cmake_minimum_required (VERSION 2.8)
set(CMAKE_INSTALL_PREFIX "/usr/local")
project(RASPB)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-O3 -static -fopenmp") 
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXE_LINKER_FLAGS "-s")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
link_directories(./include/judy-1.0.5/src/obj/.libs)
include_directories(include)
add_executable(raspberry qc.c)
target_link_libraries(raspberry
Judy
m
z
pthread
)
INSTALL (TARGETS raspberry DESTINATION /usr/local/bin)

