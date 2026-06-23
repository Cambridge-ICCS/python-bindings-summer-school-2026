cmake_minimum_required(VERSION 3.16...3.29)

project(
  plunge-python
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11
  GIT_TAG d03662f0984f652b60e7ddce53d3868002275197 # Tag v3.0.4
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(plunge_pyb MODULE src/plunge_pyb.cpp)

target_compile_options(plunge_pyb PRIVATE -Wall -Wextra)

install(TARGETS plunge_pyb LIBRARY DESTINATION .)
