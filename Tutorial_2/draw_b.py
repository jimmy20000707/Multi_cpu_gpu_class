import matplotlib.pyplot as plt

file_path = 'spring_simulation.txt'

time = []
x1 = []
x2 = []
x3 = []

with open(file_path, 'r') as file:
    header = file.readline()
    for line in file:
        data = line.split()
        time.append(float(data[0]))
        x1.append(float(data[1]))
        x2.append(float(data[4]))
        x3.append(float(data[7]))
plt.figure(figsize=(10,5))
plt.plot(time, x1, label='Mass 1 Position')
plt.plot(time, x2, label='Mass 2 Position')
plt.plot(time, x3, label='Mass 3 Position')

plt.title('')
plt.xlabel('Time (s)')
plt.ylabel('Position  (m)')

plt.legend()

#save
plt.savefig("position_plot.png")

