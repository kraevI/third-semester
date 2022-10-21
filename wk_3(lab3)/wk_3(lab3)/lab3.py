import numpy as np
import matplotlib.pyplot as plt

a = np.loadtxt("lab3_output.txt", float);
print(a)
a = a.T
print(a)

fig, ax = plt.subplots()

ax.plot(a[0], a[1])
#ax.hist(a)

plt.show()
