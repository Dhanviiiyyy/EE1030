import matplotlib.pyplot as plt


time = []
drift_distance = []

with open("drift_data.txt", "r") as file:
    next(file)  # Skip the header line
    for line in file:
        values = line.split()
        time.append(float(values[0]))
        drift_distance.append(float(values[1]))

plt.figure(figsize=(8, 6))
plt.plot(time, drift_distance, color='r', label='Drift Distance')

plt.xlabel('Time (hours)')
plt.ylabel('Drift Distance (km)')
plt.title('Drift Distance vs. Time')

plt.grid(True)
plt.legend()
plt.show()

