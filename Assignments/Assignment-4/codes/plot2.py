import matplotlib.pyplot as plt
import numpy as np


data = np.loadtxt("drift_data.txt", skiprows=1)

time = data[:, 0]
drift_distance = data[:, 1]

plt.figure(figsize=(8, 6))
plt.plot(time, drift_distance, color='r', label='Drift Distance')
plt.xlabel('Time (hours)')
plt.ylabel('Drift Distance (km)')
plt.title('Drift Distance vs. Time')

plt.grid(True)
plt.legend()
plt.show()


