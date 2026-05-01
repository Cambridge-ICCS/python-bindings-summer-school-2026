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
}

class Simulation {
public:
    // Particle data structure using Structure of Arrays (SoA)
    struct ParticleData {
        std::vector<double> masses;
        std::vector<double> positions_x;
        std::vector<double> positions_y;
        std::vector<double> positions_z;
        std::vector<double> velocities_x;
        std::vector<double> velocities_y;
        std::vector<double> velocities_z;

        // Constructor with data (same signature as before)
        ParticleData(std::vector<double> masses,
                    std::vector<double> positions_x,
                    std::vector<double> positions_y,
                    std::vector<double> positions_z,
                    std::vector<double> velocities_x,
                    std::vector<double> velocities_y,
                    std::vector<double> velocities_z);

        // Get number of particles
        auto size() const { return masses.size(); }

        // Print particle data in CSV format to provided output stream
        void printCSV(std::ostream& os) const;

    private:
        void validate() const;
    };

    // Constructor
    Simulation(double timestep, ParticleData particles);

    // Method to progress the simulation by specified time
    void progress(double time);

    const ParticleData& getParticleData() const;

    // Get elapsed time
    double getElapsedTime() const;

private:
    double timestep_;
    ParticleData particles_;
    double elapsed_time_;

    void leapFrogStep();
};

} // namespace nbody
