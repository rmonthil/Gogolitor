#!/usr/bin/python3

import math
import numpy as np
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import Axes3D

# TODO, new approach withou NRJ

g = 1.0
rho_w = 1.0
u_w = 1.0
nt = 150
dt = 0.5
x = np.linspace(-10.0, 10.0, 10000)
waves = []

# A wave is characterized by r (diameter of the wave), h_b (height of the "hole"), h_w (height of the wave), d (thickness of the wave)
def create_wave(dw, x, r, h_b):
    ## NRJ approch
    # Computing m
    #m = rho_w * math.pi * r**2 * h_b
    # Computing h_w
    #h_w = (dw/m - 0.5 * u_w**2)/g # 0.5 m u_w**2 to be checked !!!
    #h_w = dw / (m * g) # Start by neglecting kinetic energy
    # Computing d
    #d = 0.5 * r * h_b / h_w
    ## NRJ-less approach
    d = u_w * dt
    h_w = r * h_b / d
    # Return wave
    return [{"x":x - (r + 0.5*d), "dir":-1.0, "h":h_w, "d":d}, {"x":x + (r + 0.5*d), "dir":1.0, "h":h_w, "d":d}]

def h(waves, x):
    h = np.zeros(len(x))
    for i in range(len(x)):
        for w in waves:
            if x[i] < w["x"] + 0.5 * w["d"] and x[i] > w["x"] - 0.5 * w["d"]: # Is affected by this wave
                h[i] += w["h"]
    return h

# Update
p = 2.0
vp = 0.0
mp = 1.0
rp = 0.1
for n in range(nt):
    vp += -g * dt
    p += vp * dt
    h0 = h(waves, [0.0])[0]
    if p < 0.0:
        f = 1.5 * mp * g
        vp += f/mp * dt
        dw = -f * vp * dt
        #waves += create_wave(dw, 0.0, rp, h0-p)
        waves += create_wave(dw, 0.0, rp, -vp*dt)
    plt.clf()
    plt.plot(x, h(waves, x))
    plt.scatter(0, p)
    plt.axis('equal')
    plt.pause(dt)
    for w in waves:
        oldD = w["d"]
        w["d"] += 0.5 * u_w * dt
        w["x"] += w["dir"] * 0.5 * u_w * dt
        w["h"] = w["h"] * oldD / w["d"]

plt.plot(x, h(waves, x))
plt.show()
