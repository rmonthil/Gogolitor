#!/usr/bin/python3

import gogolitor as gg

import matplotlib
import matplotlib.cm as cmx
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.animation as anim

lx, ly, nx, ny = 100.0, 100.0, 100, 100
m = gg.MeshCartesianRegular(lx, ly, nx, ny) # lx, ly, nx, ny
dt = 1.0/30.0
s = gg.SolverGoudunov(m, dt) # mesh, dt

h0 = 20.0
def init_mesh(m):
    for c in m.cells:
        c.data[0] = h0 # data[0] is h, data[1] is ux, data[2] is uy
        c.data[1] = 0.0 # data[0] is h, data[1] is ux, data[2] is uy
        c.data[2] = 0.0 # data[0] is h, data[1] is ux, data[2] is uy
        c.data[3] = 0.0 # data[3] is a copy of h
        c.data[4] = 0.0

init_mesh(m)

# Lagrangian Material Point :
oy = h0 + 1.0
voy = 0.0

center = gg.Vector(2)
center[0], center[1] = lx/2.0, ly/2.0
r = 5.0
def update_lagrangian():
    global oy, voy
    bouyancy_tot = 0.0
    drag_tot = 0.0
    for c in m.cells:
        if (c.position - center).norm() < r:
            h = c.data[0]
            bouyancy = 12.0 * max(0.0, h - oy)
            if oy < h:
                drag = -0.12 * voy * abs(voy)
            else:
                drag = 0.0
            c.data[4] = -(bouyancy + drag) * dt
            bouyancy_tot += bouyancy
            drag_tot += drag
    voy += (bouyancy_tot + drag_tot + -9.81) * dt
    oy += voy * dt

# Animation 
a_fig = plt.figure()
a_ax = a_fig.add_subplot(111, projection='3d')
x = [c.position[0] for c in m.cells]
y = [c.position[1] for c in m.cells]
h = [c.data[0] for c in m.cells]
p, = a_ax.plot(x, y, h, c=(0.0, 0.0, 1.0, 0.5), linestyle='', marker='o', ms=0.5)
p2, = a_ax.plot([lx/2], [ly/2], [oy], c=(1.0, 0.0, 0.0, 0.5), linestyle='', marker='o', ms=1.0)
title = a_ax.set_title('Solver')

fps = 30.0
dt = 1.0/fps
nt = 100
speed_factor = 1.0

def a_init():
    global oy, voy
    init_mesh(m)
    oy = h0 + 1.0
    voy = 0.0
    return title, p, p2

def a_update(i):
    global x, y, h, u, oy, voy
    s.update()
    update_lagrangian()
    h = [c.data[0] for c in m.cells]
    p.set_data(x, y)
    p.set_3d_properties(h)
    p2.set_data([lx/2], [ly/2])
    p2.set_3d_properties([oy])
    title.set_text('Solver, time={}'.format(int(10*i*dt)/10))
    return title, p, p2

a = anim.FuncAnimation(a_fig, a_update, init_func=a_init, frames=nt, interval=1000.0*dt/speed_factor, blit=True, repeat_delay=1000.0)

plt.show()
