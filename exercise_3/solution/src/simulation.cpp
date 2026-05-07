#include <nbody/simulation.h>

#include <iostream>
#include <cmath>
#include <algorithm>

namespace nbody {


Simulation::Simulation(double timestep, std::vector<Particle> particles)
    : timestep_(timestep), particles_(std::move(particles)), elapsed_time_(0.0) {
    this->validateParticles();
}

void Simulation::validateParticles() const {
    if (particles_.empty()) {
        throw std::invalid_argument("Simulation must contain at least one particle");
    }

    if (std::any_of(particles_.cbegin(), particles_.cend(), 
                   [](const auto& p) { return p.mass <= 0.0; })) {
        throw std::invalid_argument("All particle masses must be positive");
    }
}

// Print particle data in CSV format to provided output stream
void Simulation::printCSV(std::ostream& os) const {
    // Print CSV header
    os << "particle_id,mass,position_x,position_y,position_z,velocity_x,velocity_y,velocity_z\n";

    // Print each particle's data
    for (size_t i = 0; i < particles_.size(); ++i) {
        const auto& p = particles_[i];
        os << i << ","
           << p.mass << ","
           << p.x << "," << p.y << "," << p.z << ","
           << p.vx << "," << p.vy << "," << p.vz << "\n";
    }
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
    auto num_particles = particles_.size();

    // Update positions: r(t + dt/2) = r(t) + v(t) * dt/2
    for (auto& particle : particles_) {
        particle.x += particle.vx * timestep_ * 0.5;
        particle.y += particle.vy * timestep_ * 0.5;
        particle.z += particle.vz * timestep_ * 0.5;
    }

    // Calculate gravitational accelerations
    std::vector<double> accel_x(num_particles, 0.0);
    std::vector<double> accel_y(num_particles, 0.0);
    std::vector<double> accel_z(num_particles, 0.0);

    // Calculate forces between all particle pairs
    for (std::size_t i = 0; i < num_particles; ++i) {
        for (std::size_t j = 0; j < num_particles; ++j) {
            if (i == j) continue;  // Skip self-interaction

            const auto& p1 = particles_[i];
            const auto& p2 = particles_[j];

            // Calculate distance vector between particles i and j
            const double dx = p2.x - p1.x;
            const double dy = p2.y - p1.y;
            const double dz = p2.z - p1.z;

            // Calculate distance squared
            const double r_squared = dx * dx + dy * dy + dz * dz;

            // Add small epsilon to avoid division by zero for very close particles
            const double r_magnitude = std::sqrt(r_squared + constants::eps);
            const double r_cubed = r_magnitude * r_magnitude * r_magnitude;

            // Calculate gravitational force (F = G * m1 * m2 / r^2)
            // Acceleration on particle i due to particle j: a = F/m = G * m_j / r^2
            // but we need acceleration vector hence need r^3 in denominator 
            // a_vec = G *m_j r / |r|^3
            const double force_factor = constants::gravitation_constant * p2.mass / r_cubed;

            // Add to acceleration arrays (force direction is from i to j)
            accel_x[i] += force_factor * dx;
            accel_y[i] += force_factor * dy;
            accel_z[i] += force_factor * dz;
        }
    }

    // Update velocities and final positions
    for (std::size_t i = 0; i < num_particles; ++i) {
        auto& particle = particles_[i];
        
        // Update velocities: v(t + dt) = v(t) + a(t + dt/2) * dt
        particle.vx += accel_x[i] * timestep_;
        particle.vy += accel_y[i] * timestep_;
        particle.vz += accel_z[i] * timestep_;

        // Final position update: r(t + dt) = r(t + dt/2) + v(t + dt) * dt/2
        particle.x += particle.vx * timestep_ * 0.5;
        particle.y += particle.vy * timestep_ * 0.5;
        particle.z += particle.vz * timestep_ * 0.5;
    }
}



double Simulation::getElapsedTime() const {
    return elapsed_time_;
}

} // namespace nbody
