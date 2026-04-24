cmake_minimum_required(VERSION 3.15)

# Project name
project(NBodySimulation LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library from source files
add_library(simulation_lib STATIC
    src/simulation.cpp
)

# Include directories
include_directories(include)

# Create the run_simple executable
add_executable(run_simple
    apps/run_simple.cpp
)

# Link the executable with our library
target_link_libraries(run_simple
    simulation_lib
)
