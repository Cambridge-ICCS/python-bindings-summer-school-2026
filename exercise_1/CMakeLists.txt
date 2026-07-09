cmake_minimum_required(VERSION 3.16...3.29)

project(
  plunge-python
  VERSION 0.1.0
  LANGUAGES C CXX)

find_package(
  Python
  COMPONENTS Development.Module
  REQUIRED)

python_add_library(plunge_ex MODULE src/plunge_ex.cpp WITH_SOABI)

set_property(TARGET plunge_ex PROPERTY CXX_STANDARD 17)
set_property(TARGET plunge_ex PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET plunge_ex PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(plunge_ex PRIVATE -Wall -Wextra)

install(TARGETS plunge_ex LIBRARY DESTINATION .)
