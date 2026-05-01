#include <pybind11/pybind11.h>

#include <simulation.h>


namespace py = pybind11;

PYBIND11_MODULE(nbody, m) {
    m.doc() = R"pbdoc(
        Simple N-body simulator for 2026 ICCS Summer School
        ---------------------------------------------------

        Contains Python bindings to a simple N-body simulator.
        
        We will use it to create some nice plots with matplotlib ;-) 
    )pbdoc";

    m.attr("__version__") = "0.1.0";
}
