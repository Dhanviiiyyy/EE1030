import matplotlib.pyplot as plt
import numpy as np

v_s = np.array([0, 4.0])  # Swimmer's velocity in still water
v_r = np.array([3.0, 0])  # River current velocity
v_res = v_s + v_r         # Resultant velocity

plt.figure()
plt.quiver(0, 0, v_s[0], v_s[1], angles='xy', scale_units='xy', scale=1, color='b', label='Swimmer Velocity (v_s)')
plt.quiver(0, 0, v_r[0], v_r[1], angles='xy', scale_units='xy', scale=1, color='g', label='River Current (v_r)')
plt.quiver(0, 0, v_res[0], v_res[1], angles='xy', scale_units='xy', scale=1, color='r', label='Resultant Velocity (v_res)')

plt.xlim(-1, 5)
plt.ylim(-1, 5)
plt.xlabel('Horizontal Component (km/h)')
plt.ylabel('Vertical Component (km/h)')


plt.grid()
plt.legend()
plt.gca().set_aspect('equal', adjustable='box')
plt.title("Swimmer's Velocity, River Current, and Resultant Velocity")
plt.show()
