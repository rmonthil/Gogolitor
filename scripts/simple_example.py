#!/usr/bin/python3

import gogolitor as gg

import matplotlib
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.animation as anim

lx, ly, nx, ny = 100.0, 100.0, 100, 100
m = gg.MeshCartesianRegular(lx, ly, nx, ny) # lx, ly, nx, ny
s = gg.SolverGoudunov(m, 1.0/30.0) # mesh, dt

def init_mesh(m):
    h0 = 20.0
    center = gg.Vector(2)
    center[0], center[1] = lx/2.0, ly/2.0
    r = 15.0
    hr = h0 + 0.0
    fr = 0.0
    for c in m.cells:
        if (c.position - center).norm() < r:
            c.data[0] = hr # data[0] is h, data[1] is ux, data[2] is uy
            c.data[4] = fr # data[4] is a source terme
        else:
            c.data[0] = h0 # data[0] is h, data[1] is ux, data[2] is uy
            c.data[4] = 0.0
        c.data[1] = 0.0 # data[0] is h, data[1] is ux, data[2] is uy
        c.data[2] = 0.0 # data[0] is h, data[1] is ux, data[2] is uy
        c.data[3] = 0.0 # data[3] is a copy of h

init_mesh(m)

# Animation 
a_fig = plt.figure()
a_ax = a_fig.add_subplot(111, projection='3d')
x = [c.position[0] for c in m.cells]
y = [c.position[1] for c in m.cells]
h = [c.data[0] for c in m.cells]
p, = a_ax.plot(x, y, h, c=(0.0, 0.0, 1.0, 0.5), linestyle='', marker='o', ms=0.5)
title = a_ax.set_title('Solver')

fps = 30.0
dt = 1.0/fps
nt = 600
speed_factor = 1.0

def a_init():
    init_mesh(m)
    return title, p

def a_update(i):
    global x, y, h, u
    s.update()
    h = [c.data[0] for c in m.cells]
    p.set_data(x, y)
    p.set_3d_properties(h)
    title.set_text('Solver, time={}'.format(int(10*i*dt)/10))
    return title, p

a = anim.FuncAnimation(a_fig, a_update, init_func=a_init, frames=nt, interval=1000.0*dt/speed_factor, blit=True, repeat_delay=1000.0)

plt.show()
