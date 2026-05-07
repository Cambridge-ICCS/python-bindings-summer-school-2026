#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <nbody/simulation.h>

#include <sstream>

namespace py = pybind11;

using py::literals::operator""_a;

void bind_particle(py::module_ &m) {
  py::class_<nbody::Simulation::Particle>(m, "Particle")
      .def(py::init<double, double, double, double, double, double, double>(), "Docstring", "x"_a,
           "y"_a, "z"_a, "vx"_a, "vy"_a, "vz"_a, "mass"_a)
      .def_readwrite("mass", &nbody::Simulation::Particle::mass)
      .def_readwrite("x", &nbody::Simulation::Particle::x)
      .def_readwrite("y", &nbody::Simulation::Particle::y)
      .def_readwrite("z", &nbody::Simulation::Particle::z)
      .def_readwrite("vx", &nbody::Simulation::Particle::vx)
      .def_readwrite("vy", &nbody::Simulation::Particle::vy)
      .def_readwrite("vz", &nbody::Simulation::Particle::vz)
      .def("__repr__", [](const nbody::Simulation::Particle &p) {
        std::stringstream msg;
        msg << "nbody.Particle(";
        msg << "mass=" << p.mass << ",";
        msg << "x=" << p.x << ",";
        msg << "y=" << p.y << ",";
        msg << "z=" << p.z << ",";
        msg << "vx=" << p.vx << ",";
        msg << "vy=" << p.vy << ",";
        msg << "vz=" << p.vz;
        msg << ")";
        return msg.str();
      });
}

PYBIND11_MODULE(nbody, m) {
  m.doc() = R"pbdoc(
        Simple N-body simulator for 2026 ICCS Summer School
        ---------------------------------------------------

        Contains Python bindings to a simple N-body simulator.
        
        We will use it to create some nice plots with matplotlib ;-) 
    )pbdoc";

  m.attr("__version__") = "0.1.0";

  bind_particle(m);
}
