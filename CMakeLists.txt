cmake_minimum_required(VERSION 3.10)
project(gol C)

# Compiler options
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99 -g")

# Include directories
include_directories(inc)

# Source files
file(GLOB SOURCES "src/*.c")

# Executable
add_executable(gol ${SOURCES})

# Define preprocessor macros
target_compile_definitions(gol PRIVATE REFRESH_RATE=60 STEPS=4)
