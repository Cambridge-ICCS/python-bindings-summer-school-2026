cmake_minimum_required(VERSION 3.16)

project(
  plunge-python
  VERSION 0.1.0
  LANGUAGES C CXX)

# This is probably still abuse but I want to be able to make pure CMake build
# At least fo now...
# find_package(Python REQUIRED COMPONENTS Interpreter)
# execute_process(
#   COMMAND "${Python_EXECUTABLE}" -c
#     "import skbuild, os; print(os.path.join(os.path.dirname(skbuild.__file__), 'resources', 'cmake'), end='')"
#   OUTPUT_VARIABLE _SKBUILD_CMAKE_DIR
#   COMMAND_ERROR_IS_FATAL ANY
# )
# list(APPEND CMAKE_MODULE_PATH "${_SKBUILD_CMAKE_DIR}")


find_package(PythonExtensions REQUIRED)

add_library(_plunge MODULE src/plunge/_plunge.cxx)
python_extension_module(_plunge)

# We need to build to the right "mirror directory"
# The `_init__` file gets installed with the `src` prefix and 
# then picked-up by the setuptools(?) from the cmake-install directory
# It is still a bit unclear how this works
install(TARGETS _plunge LIBRARY DESTINATION "src/plunge")


