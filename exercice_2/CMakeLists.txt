# CMakeLists.txt - Climate Thermodynamics Library (thermolib)
#
# Modern Fortran implementation for climate science calculations
# Linux-only build configuration for gfortran
#
# Usage: mkdir build && cd build && cmake .. && make

cmake_minimum_required(VERSION 3.12)
project(thermolib LANGUAGES Fortran)

# Project metadata
set(PROJECT_VERSION "1.0.0")
set(PROJECT_DESCRIPTION "Climate Thermodynamics Library - Modern Fortran Implementation")
set(PROJECT_AUTHOR "Climate Science Team")
set(PROJECT_LICENSE "MIT")

# Linux + gfortran specific configuration
message(STATUS "Configuring thermolib for Linux with gfortran")

# Require Fortran 2008 standard
set(CMAKE_Fortran_STANDARD 2008)
set(CMAKE_Fortran_STANDARD_REQUIRED ON)

# Enable position independent code for shared library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Use standard CMake build types instead of custom flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

# Enable IEEE arithmetic for proper NaN handling
add_compile_definitions(USE_IEEE_ARITHMETIC)

# Source files - pure Fortran implementation
set(SOURCE_FILES
    src/thermo_constants.f90
    src/thermo_moisture.f90
    src/thermo_radiation.f90
    src/thermolib.f90
)

# Create shared library (Linux .so file)
add_library(thermolib SHARED ${SOURCE_FILES})

# Set library properties for Linux
set_target_properties(thermolib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    Fortran_MODULE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/modules"
    OUTPUT_NAME "thermolib"
    DEBUG_POSTFIX "d"  # Add 'd' suffix for debug builds
)

# TODO: Revisit this I need to exort module files.
target_include_directories(thermolib
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(thermolib PRIVATE -Wall -Wextra)

# Linux-specific installation
install(TARGETS thermolib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install Fortran module files
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/modules/
    DESTINATION lib/thermolib
)

# Add test executable
add_executable(test_thermolib test_thermolib.f90)
target_link_libraries(test_thermolib PUBLIC thermolib)

# Add include directory for module files
target_include_directories(test_thermolib PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/modules)

# # Add custom target to run tests
# add_custom_target(run_tests
#     COMMAND test_thermolib
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     DEPENDS test_thermolib
#     COMMENT "Running thermolib tests"
#     VERBATIM
# )

# Display build information
message(STATUS "thermolib ${PROJECT_VERSION} configured successfully")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Fortran compiler: ${CMAKE_Fortran_COMPILER}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
