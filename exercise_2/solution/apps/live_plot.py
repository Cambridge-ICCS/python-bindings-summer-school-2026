import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import nbody

# Settings
simulation_timestep = 0.0005  # yr
animation_timestep = 0.005  # yr per frame
total_simulation_time = 1.0  # yr


def get_particle_positions_copy(sim: nbody.Simulation) -> np.ndarray:
    """
    Return an array of particle positions.

    Uses the 'copy interface'

    Parameters
    ----------
    sim : nbody.Simulation

    Result
    ------
    np.ndarray
        An array of shape (N, 3) containing the positions of the N particles.
    """
    particles = sim.get_particles()
    positions = np.empty((len(particles), 3), dtype=np.float64)
    for i, p in enumerate(particles):
        positions[i, 0] = p.position.x
        positions[i, 1] = p.position.y
        positions[i, 2] = p.position.z
    return positions


def get_particle_positions_view(sim: nbody.Simulation) -> np.ndarray:
    """
    Return an array of particle positions.

    Uses the 'view interface'

    Parameters
    ----------
    sim : nbody.Simulation

    Result
    ------
    np.ndarray
        An array of shape (N, 3) containing the positions of the N particles.
    """
    view = sim.get_particles_view()
    return view.view(np.float64).reshape(len(view), -1)


# get_particles_positions = get_particle_positions_copy
get_particles_positions = get_particle_positions_copy


# Figure-8 three body choreography
# Values taken from: https://arxiv.org/pdf/math/0011268
TWO_PI = 2.0 * np.pi
M = 1.0
sim = nbody.Simulation(
    dt=0.0005,
    particles=[
        nbody.Particle(
            nbody.Vector3(0.97000436, -0.24308753, 0),
            nbody.Vector3(0.46620369 * TWO_PI, 0.43236573 * TWO_PI, 0),
            M,
        ),
        nbody.Particle(
            nbody.Vector3(0, 0, 0),
            nbody.Vector3(-0.93240737 * TWO_PI, -0.86473146 * TWO_PI, 0),
            M,
        ),
        nbody.Particle(
            nbody.Vector3(-0.97000436, 0.24308753, 0),
            nbody.Vector3(0.46620369 * TWO_PI, 0.43236573 * TWO_PI, 0),
            M,
        ),
    ],
)


# Variables to save the trails of the particles
trails_x = [list() for _ in range(sim.n_particles)]
trails_y = [list() for _ in range(sim.n_particles)]

# Set-up the plot
fig, ax = plt.subplots(figsize=(7, 7))
ax.set_xlim(-1.3, 1.3)
ax.set_ylim(-1.3, 1.3)
ax.set_aspect("equal")
ax.set_xlabel("x (AU)")
ax.set_ylabel("y (AU)")
ax.grid(True, linestyle="--", alpha=0.5)
time_text = ax.text(0.02, 0.96, "", transform=ax.transAxes, fontsize=9, va="top")

(line_a,) = ax.plot([], [], color="orange", lw=1.5, label="Body A")
(line_b,) = ax.plot([], [], color="royalblue", lw=1.5, label="Body B")
(line_c,) = ax.plot([], [], color="tomato", lw=1.5, label="Body C")
dot_a = ax.scatter([], [], color="orange", s=100, zorder=5, marker="o")
dot_b = ax.scatter([], [], color="royalblue", s=100, zorder=5, marker="o")
dot_c = ax.scatter([], [], color="tomato", s=100, zorder=5, marker="o")

ax.legend(loc="upper right")
plt.tight_layout()


# Animation update
def update(_frame):
    """Advance the simulation by one frame and refresh the plot artists."""
    if sim.get_elapsed_time() >= total_simulation_time:
        ani.event_source.stop()
        return

    sim.progress(animation_timestep)

    particle_positions = get_particle_positions_view(sim)

    for i in range(sim.n_particles):
        trails_x[i].append(particle_positions[i, 0])
        trails_y[i].append(particle_positions[i, 1])

    line_a.set_data(trails_x[0], trails_y[0])
    line_b.set_data(trails_x[1], trails_y[1])
    line_c.set_data(trails_x[2], trails_y[2])
    dot_a.set_offsets([[trails_x[0][-1], trails_y[0][-1]]])
    dot_b.set_offsets([[trails_x[1][-1], trails_y[1][-1]]])
    dot_c.set_offsets([[trails_x[2][-1], trails_y[2][-1]]])

    time_text.set_text(f"t = {sim.get_elapsed_time():.2f} yr")


n_frames = int(total_simulation_time / animation_timestep)
ani = animation.FuncAnimation(fig, update, frames=n_frames, interval=30, cache_frame_data=False)
ani.save(filename="figure8_orbit.gif", writer="pillow")
