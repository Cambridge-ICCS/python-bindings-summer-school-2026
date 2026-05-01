cmake_minimum_required(VERSION 3.15)

# Project name
project(
  NBodySimulation
  LANGUAGES CXX
  VERSION 0.1.0)

option(NBODY_PYTHON_BINDINGS "Set  to true to build Python bindings" ON)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library from source files
add_library(simulation_lib STATIC src/simulation.cpp)

# Include directories
include_directories(include)

# Create the run_simple executable
add_executable(run_simple apps/run_simple.cpp)

# Link the executable with our library
target_link_libraries(run_simple simulation_lib)

# Build Python bindings
if(NBODY_PYTHON_BINDINGS)
  set(PYBIND11_FINDPYTHON
      NEW
      CACHE STRING "Use the new Pybind11 discovery" FORCE)

  include(FetchContent)
  # We use CMake FetchContent to download the pybind11 dependency for us See:
  # https://cmake.org/cmake/help/latest/module/FetchContent.html
  FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    # It is good practice to point to specific commits instead of branches or
    # tags It is for security reasons (in case repository gets spoofed)
    GIT_TAG d03662f0984f652b60e7ddce53d3868002275197 # Tag v3.0.4
  )

  FetchContent_MakeAvailable(pybind11)

  add_subdirectory(python)
endif()
