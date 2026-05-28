pybind11_add_module(nbody MODULE ./nbody_pymodule.cpp)

target_link_libraries(nbody PRIVATE simulation_lib)
target_link_libraries(nbody PRIVATE pybind11::headers)

install(TARGETS nbody DESTINATION .)
