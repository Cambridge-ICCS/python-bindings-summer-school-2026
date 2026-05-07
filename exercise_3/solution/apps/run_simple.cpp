#include <nbody/simulation.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    // Earth-Sun system in astronomical units (AU), solar masses, years
    const double earth_velocity = std::sqrt(nbody::constants::gravitation_constant * nbody::constants::solar_mass);

    // Create particles using flattened AoS structure
    std::vector<nbody::Simulation::Particle> particles = {
        // Particle 0: Sun (at origin, stationary)
        {
            0.0, 0.0, 0.0,        // x, y, z
            0.0, 0.0, 0.0,        // vx, vy, vz
            nbody::constants::solar_mass
        },
        // Particle 1: Earth (at 1 AU on x-axis, moving in +y direction)
        {
            1.0, 0.0, 0.0,        // x, y, z
            0.0, earth_velocity, 0.0,  // vx, vy, vz
            nbody::constants::earth_mass
        }
    };

    const double timestep = 0.001;
    const double print_interval  = 0.01;
    const double total_time = 0.5;

    nbody::Simulation sim(timestep, std::move(particles));

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "time(yr)   sun_x(AU)   sun_y(AU)   earth_x(AU)   earth_y(AU)\n";

    // Print state helper
    auto printState = [&]() {
        const auto& particles = sim.getParticles();
        std::cout << sim.getElapsedTime()
                  << "   " << particles[0].x << "   " << particles[0].y
                  << "   " << particles[1].x << "   " << particles[1].y
                  << "\n";
    };

    printState();

    while (sim.getElapsedTime() < total_time - 0.5 * print_interval) {
        sim.progress(print_interval);
        printState();
    }

    return 0;
}
