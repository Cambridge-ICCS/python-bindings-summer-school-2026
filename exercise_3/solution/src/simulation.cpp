#include <simulation.h>

#include <iostream>
#include <cmath>
#include <algorithm>

namespace nbody {

// ParticleData constructor with validation
Simulation::ParticleData::ParticleData(std::vector<double> masses,
                                      std::vector<double> positions_x,
                                      std::vector<double> positions_y,
                                      std::vector<double> positions_z,
                                      std::vector<double> velocities_x,
                                      std::vector<double> velocities_y,
                                      std::vector<double> velocities_z)
    : masses(std::move(masses)),
      positions_x(std::move(positions_x)),
      positions_y(std::move(positions_y)),
      positions_z(std::move(positions_z)),
      velocities_x(std::move(velocities_x)),
      velocities_y(std::move(velocities_y)),
      velocities_z(std::move(velocities_z)) {
    this->validate();
}

// Validate that all arrays have the same size
void Simulation::ParticleData::validate() const {
    size_t num_particles = masses.size();
    if (positions_x.size() != num_particles ||
        positions_y.size() != num_particles ||
        positions_z.size() != num_particles ||
        velocities_x.size() != num_particles ||
        velocities_y.size() != num_particles ||
        velocities_z.size() != num_particles) {
        throw std::invalid_argument("All particle arrays must have the same size");
    }

    // Throw is any mass is negative
    if (std::any_of(masses.cbegin(), masses.cend(), [](const auto m) {return m <= 0.0;})) {
        throw std::invalid_argument("All masses must be positive");
    }

}

// Print particle data in CSV format to provided output stream
void Simulation::ParticleData::printCSV(std::ostream& os) const {
    // Print CSV header
    os << "particle_id,mass,position_x,position_y,position_z,velocity_x,velocity_y,velocity_z\n";

    // Print each particle's data
    for (size_t i = 0; i < size(); ++i) {
        os << i << ","
           << masses[i] << ","
           << positions_x[i] << ","
           << positions_y[i] << ","
           << positions_z[i] << ","
           << velocities_x[i] << ","
           << velocities_y[i] << ","
           << velocities_z[i] << "\n";
    }
}

// Simulation constructor
Simulation::Simulation(double timestep, ParticleData particles)
    : timestep_(timestep), particles_(std::move(particles)), elapsed_time_(0.0) {
}

void Simulation::progress(double time) {

    if (time < 0) {
        throw std::domain_error("Time to advance forward must be non-negative.");
    }

    // Calculate number of steps needed
    int num_steps = static_cast<int>(std::round(time / timestep_));

    // Perform leap-frog integration steps
    for (int i = 0; i < num_steps; ++i) {
        leapFrogStep();
    }

    elapsed_time_ += num_steps * timestep_;
}

void Simulation::leapFrogStep() {
    size_t num_particles = particles_.size();
    const auto& masses = particles_.masses;
    auto& positions_x = particles_.positions_x;
    auto& positions_y = particles_.positions_y;
    auto& positions_z = particles_.positions_z;
    auto& velocities_x = particles_.velocities_x;
    auto& velocities_y = particles_.velocities_y;
    auto& velocities_z = particles_.velocities_z;

    // Update positions: r(t + dt/2) = r(t) + v(t) * dt/2
    for (size_t i = 0; i < num_particles; ++i) {
        positions_x[i] += velocities_x[i] * timestep_ * 0.5;
        positions_y[i] += velocities_y[i] * timestep_ * 0.5;
        positions_z[i] += velocities_z[i] * timestep_ * 0.5;
    }

    // Calculate gravitational accelerations for all particles
    // Using Newton's law of universal gravitation: F = G * m1 * m2 / r^2

    // Temporary arrays to store accelerations
    std::vector<double> accel_x(num_particles, 0.0);
    std::vector<double> accel_y(num_particles, 0.0);
    std::vector<double> accel_z(num_particles, 0.0);

    // Calculate gravitational forces between all particle pairs
    for (size_t i = 0; i < num_particles; ++i) {
        for (size_t j = 0; j < num_particles; ++j) {
            if (i == j) continue;  // Skip self-interaction

            // Calculate distance vector between particles i and j
            const double dx = positions_x[j] - positions_x[i];
            const double dy = positions_y[j] - positions_y[i];
            const double dz = positions_z[j] - positions_z[i];

            // Calculate distance squared
            const double r_squared = dx * dx + dy * dy + dz * dz;

            // Add small epsilon to avoid division by zero for very close particles
            const double r_magnitude = std::sqrt(r_squared + constants::eps);
            const double r_cubed = r_magnitude * r_magnitude * r_magnitude;

            // Calculate gravitational force (F = G * m1 * m2 / r^2)
            // Acceleration on particle i due to particle j: a = F/m = G * m_j / r^2
            const double force_factor = constants::gravitation_constant * masses[j] / r_cubed;

            // Add to acceleration arrays (force direction is from i to j)
            accel_x[i] += force_factor * dx;
            accel_y[i] += force_factor * dy;
            accel_z[i] += force_factor * dz;
        }
    }

    // Update velocities: v(t + dt) = v(t) + a(t + dt/2) * dt
    for (size_t i = 0; i < num_particles; ++i) {
        velocities_x[i] += accel_x[i] * timestep_;
        velocities_y[i] += accel_y[i] * timestep_;
        velocities_z[i] += accel_z[i] * timestep_;
    }

    // Final position update: r(t + dt) = r(t + dt/2) + v(t + dt) * dt/2
    for (size_t i = 0; i < num_particles; ++i) {
        positions_x[i] += velocities_x[i] * timestep_ * 0.5;
        positions_y[i] += velocities_y[i] * timestep_ * 0.5;
        positions_z[i] += velocities_z[i] * timestep_ * 0.5;
    }
}

const Simulation::ParticleData& Simulation::getParticleData() const {
    return particles_;
}

double Simulation::getElapsedTime() const {
    return elapsed_time_;
}

} // namespace nbody
