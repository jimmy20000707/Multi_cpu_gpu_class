import matplotlib.pyplot as plt


file_path = 'LK.txt'

time = []
x = []
y = []

with open(file_path, 'r') as file:
    for line in file:
        data = line.split()
        time.append(float(data[0]))
        x.append(float(data[1]))
        y.append(float(data[2]))

plt.plot(time, x, label='prey')
plt.plot(time, y, label='predator')

plt.title('LK draw')
plt.xlabel('Time (s)')
plt.ylabel('Population')

plt.legend()

#save
plt.savefig("LK_plot.png")
