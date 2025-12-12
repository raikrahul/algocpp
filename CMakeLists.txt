cmake_minimum_required(VERSION 3.15)
project(algocpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Collect all .cpp files
file(GLOB_RECURSE CPP_SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Create executables for each .cpp file
foreach(cpp_file ${CPP_SOURCES})
    get_filename_component(exec_name ${cpp_file} NAME_WE)
    add_executable(${exec_name} ${cpp_file})
endforeach()
