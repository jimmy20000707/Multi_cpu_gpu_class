import matplotlib.pyplot as plt

file_path = 'spring_simulation.txt'

time = []
acceleration1 = []
acceleration2 = []
acceleration3 = []

with open(file_path, 'r') as file:
    header = file.readline()
    for line in file:
        data = line.split()
        time.append(float(data[0]))
        acceleration1.append(float(data[3]))
        acceleration2.append(float(data[6]))
        acceleration3.append(float(data[9]))

plt.plot(time, acceleration1, label='Mass 1 Acceleration')
plt.plot(time, acceleration2, label='Mass 2 Acceleration')
plt.plot(time, acceleration3, label='Mass 3 Acceleration')

plt.title('Acceleration vs Time')
plt.xlabel('Time (s)')
plt.ylabel('Acceleration (m/s^2)')

plt.legend()

#save
plt.savefig("acceleration_plot.png")

