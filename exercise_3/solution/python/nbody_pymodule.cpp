#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include <nbody/simulation.h>

#include <sstream>

namespace py = pybind11;

using py::literals::operator""_a;

void bind_vector3(py::module_ &m) {
  py::class_<nbody::Vector3>(m, "Vector3")
      .def(py::init<double, double, double>(), "x"_a = 0.0, "y"_a = 0.0, "z"_a = 0.0)
      .def_readwrite("x", &nbody::Vector3::x)
      .def_readwrite("y", &nbody::Vector3::y)
      .def_readwrite("z", &nbody::Vector3::z)
      .def("__repr__", [](const nbody::Vector3 &v) {
        std::stringstream msg;
        msg << "nbody.Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return msg.str();
      });
}

void bind_particle(py::module_ &m) {
  py::class_<nbody::Simulation::Particle>(m, "Particle")
      .def(py::init([](nbody::Vector3 position, nbody::Vector3 velocity, double mass) {
             return nbody::Simulation::Particle{position, velocity, mass};
           }),
           "position"_a, "velocity"_a, "mass"_a)
      .def_readwrite("mass", &nbody::Simulation::Particle::mass)
      .def_readwrite("velocity", &nbody::Simulation::Particle::velocity)
      .def_readwrite("position", &nbody::Simulation::Particle::position)
      .def("__repr__", [](const nbody::Simulation::Particle &p) {
        std::stringstream msg;
        msg << "nbody.Particle(";
        msg << "position=nbody.Vector3(" << p.position.x << ", " << p.position.y << ", "
            << p.position.z << "), ";
        msg << "velocity=nbody.Vector3(" << p.velocity.x << ", " << p.velocity.y << ", "
            << p.velocity.z << "), ";
        msg << "mass=" << p.mass;
        msg << ")";
        return msg.str();
      });
}

void bind_simulation(py::module_ &m) {

  // Register numpy dtypes — Vector3 must be registered before Particle
  PYBIND11_NUMPY_DTYPE(nbody::Vector3, x, y, z);
  PYBIND11_NUMPY_DTYPE(nbody::Simulation::Particle, position, velocity, mass);

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

  // Store constants
  m.attr("EARTH_MASS") = nbody::constants::earth_mass;
  m.attr("SOLAR_MASS") = nbody::constants::solar_mass;
  m.attr("GRAVITATION_CONSTANT") = nbody::constants::gravitation_constant;

  bind_vector3(m);
  bind_particle(m);
  bind_simulation(m);
}
