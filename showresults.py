import dnest4.classic as dn4
dn4.postprocess()

import matplotlib.pyplot as plt
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")

# Plot some curves through the data
x_data = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0]
y_data = [1.0, 3.8, 3.7, 3.8, 2.9, 2.4, 2.0, 1.3, 0.4, -0.2]
plt.plot(x_data, y_data, "o")

for i in range(0, 10):
    plt.plot(x_data, posterior_sample[i, 2:], color="g", alpha=0.2)

plt.show()

