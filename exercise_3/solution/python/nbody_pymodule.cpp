#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

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

void bind_simulation(py::module_ &m) {

  // This sets-up Numpy dtype to which `Particle` struct will be mapped
  PYBIND11_NUMPY_DTYPE(nbody::Simulation::Particle, x, y, z, vx, vy, vz, mass);

  py::class_<nbody::Simulation>(m, "Simulation")
      .def(py::init<double, std::vector<nbody::Simulation::Particle>>(), "Docstring", "dt"_a,
           "particles"_a)
      // Alternative version, provide nullptr for setter
      // It is equivalent to `def_property_readonly
      //.def_property("dt", &nbody::Simulation::getTimestep, nullptr)
      .def_property_readonly("dt", &nbody::Simulation::getTimestep)
      .def("progress", &nbody::Simulation::progress, "Advance the simulation by the given time",
           "time"_a)
      .def("get_elapsed_time", &nbody::Simulation::getElapsedTime,
           "Return the total elapsed simulation time")
      .def("get_particles", &nbody::Simulation::getParticles,
           "Return the list of particles (makes a copy)")
      .def(
          "get_particles_view",
          [](nbody::Simulation &sim) {
            const auto &particles = sim.getParticles();

            // Construct a Numpy array
            // Pybind11 will convert
            auto arr = py::array_t<nbody::Simulation::Particle>(
                {particles.size()},                    // <- This is shape
                {sizeof(nbody::Simulation::Particle)}, // <- These are strides in bytes
                particles.data(),                      // <- Row pointer to the data
                py::cast(sim) // <- Reference to object that controls the lifetime
            );

            // pybind11 numpy array is writable by default
            // To keep the view read-only we need to set a flag
            arr.attr("flags").attr("writeable") = false;
            return arr;
          },
          "Return a numpy structured array view of particles (no copy)");
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
  bind_simulation(m);
}
