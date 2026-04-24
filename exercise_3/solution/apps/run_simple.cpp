#include <simulation.h>

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    // Earth-Sun system in astronomical units (AU), solar masses, years
    const double earth_velocity = std::sqrt(nbody::constants::gravitation_constant * nbody::constants::solar_mass);

    // Particle 0: Sun  (at origin, stationary)
    // Particle 1: Earth (at 1 AU on x-axis, moving in +y direction)
    nbody::Simulation::ParticleData particles(
        /*masses*/      {nbody::constants::solar_mass, nbody::constants::earth_mass},
        /*positions_x*/ {0.0, 1.0},
        /*positions_y*/ {0.0, 0.0},
        /*positions_z*/ {0.0, 0.0},
        /*velocities_x*/ {0.0,  0.0},
        /*velocities_y*/ {0.0,  earth_velocity},
        /*velocities_z*/ {0.0,  0.0}
    );

    const double timestep = 0.001;
    const double print_interval  = 0.05;
    const double total_time = 0.5;

    nbody::Simulation sim(timestep, particles);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "time(yr)   sun_x(AU)   sun_y(AU)   earth_x(AU)   earth_y(AU)\n";

    // Print state helper
    auto printState = [&]() {
        const auto& p = sim.getParticleData();
        std::cout << sim.getElapsedTime()
                  << "   " << p.positions_x[0] << "   " << p.positions_y[0]
                  << "   " << p.positions_x[1] << "   " << p.positions_y[1]
                  << "\n";
    };

    printState();

    while (sim.getElapsedTime() < total_time - 0.5 * print_interval) {
        sim.progress(print_interval);
        printState();
    }

    return 0;
}
