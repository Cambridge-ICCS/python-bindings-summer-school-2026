#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>

namespace nbody {

// The code is working in the astronomical units
//   mass: solar_mass
//   length: astronomical unit [AU]
//   time: years
namespace constants {
  constexpr double gravitation_constant = 4.0 * M_PI * M_PI;
  constexpr double eps = 1.0e-6;
  constexpr double earth_mass = 3.003e-6;
  constexpr double solar_mass = 1.0;
} // namespace constants

class Simulation {
public:
  struct Particle {
    double x, y, z;    // Position components
    double vx, vy, vz; // Velocity components
    double mass;       // Particle mass
  };

  Simulation(double timestep, std::vector<Particle> particles);

  // Method to progress the simulation by specified time
  void progress(double time);

  const auto &getParticles() const { return particles_; }

  auto numParticles() const { return particles_.size(); }

  // Print particle data in CSV format to provided output stream
  void printCSV(std::ostream &os) const;

  double getElapsedTime() const;

  double getTimestep() const { return timestep_; }

private:
  double timestep_;
  std::vector<Particle> particles_;
  double elapsed_time_;

  void leapFrogStep();
  void validateParticles() const;
};

} // namespace nbody
