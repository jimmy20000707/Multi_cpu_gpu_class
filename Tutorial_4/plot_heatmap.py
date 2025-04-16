import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

data = np.loadtxt('matrix.txt')
data_reshaped = data.reshape(100, 100)
sns.heatmap(data_reshaped)
plt.savefig('heatmap.png')

