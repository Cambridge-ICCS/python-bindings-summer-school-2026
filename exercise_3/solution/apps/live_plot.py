import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import nbody

# Settings 
simulation_timestep = 0.0005  # yr
animation_timestep = 0.005   # yr per frame
total_simulation_time = 4.0  # yr

# Figure-8 three body choreography 
# Values taken from: https://arxiv.org/pdf/math/0011268
TWO_PI = 2.0 * math.pi
M = 1.0
sim = nbody.Simulation(
    dt=0.0005,
    particles=[
        nbody.Particle(
            nbody.Vector3( 0.97000436, -0.24308753, 0),
            nbody.Vector3( 0.46620369 * TWO_PI,  0.43236573 * TWO_PI, 0),
            M,
        ),
        nbody.Particle(
            nbody.Vector3(0, 0, 0),
            nbody.Vector3(-0.93240737 * TWO_PI, -0.86473146 * TWO_PI, 0),
            M,
        ),
        nbody.Particle(
            nbody.Vector3(-0.97000436,  0.24308753, 0),
            nbody.Vector3( 0.46620369 * TWO_PI,  0.43236573 * TWO_PI, 0),
            M,
        ),
    ],
)


# Variables to save the trails of the particles
trail_x = [[], [], []]
trail_y = [[], [], []]

#Set-up the plot

fig, ax = plt.subplots(figsize=(7, 7))
ax.set_xlim(-1.3, 1.3)
ax.set_ylim(-1.3, 1.3)
ax.set_aspect("equal")
ax.set_xlabel("x (AU)")
ax.set_ylabel("y (AU)")
ax.grid(True, linestyle="--", alpha=0.5)
time_text = ax.text(0.02, 0.96, "", transform=ax.transAxes, fontsize=9, va="top")

line_a, = ax.plot([], [], color="orange",    lw=1.5, label="Body A")
line_b, = ax.plot([], [], color="royalblue", lw=1.5, label="Body B")
line_c, = ax.plot([], [], color="tomato",    lw=1.5, label="Body C")
dot_a = ax.scatter([], [], color="orange",    s=100, zorder=5, marker="o")
dot_b = ax.scatter([], [], color="royalblue", s=100, zorder=5, marker="o")
dot_c = ax.scatter([], [], color="tomato",    s=100, zorder=5, marker="o")

ax.legend(loc="upper right")
plt.tight_layout()

# Animation update

def update(_frame):
    if sim.get_elapsed_time() >= total_simulation_time:
        ani.event_source.stop()
        return

    sim.progress(animation_timestep)
    p = sim.get_particles()

    for i in range(3):
        trail_x[i].append(p[i].position.x)
        trail_y[i].append(p[i].position.y)

    line_a.set_data(trail_x[0], trail_y[0])
    line_b.set_data(trail_x[1], trail_y[1])
    line_c.set_data(trail_x[2], trail_y[2])
    dot_a.set_offsets([[trail_x[0][-1], trail_y[0][-1]]])
    dot_b.set_offsets([[trail_x[1][-1], trail_y[1][-1]]])
    dot_c.set_offsets([[trail_x[2][-1], trail_y[2][-1]]])

    time_text.set_text(f"t = {sim.get_elapsed_time():.2f} yr")

ani = animation.FuncAnimation(fig, update, interval=30, cache_frame_data=False)
plt.show()
