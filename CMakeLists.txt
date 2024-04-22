cmake_minimum_required(VERSION 3.10)
project(gol)

# Compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -pedantic")

# Add argparse library
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/morrisfranken/argparse.git
    GIT_TAG master
)
FetchContent_MakeAvailable(argparse)

# Include directories
include_directories(${argparse_SOURCE_DIR}/include/argparse inc)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Executable
add_executable(gol ${SOURCES})

# Link argparse library
target_link_libraries(gol argparse)
