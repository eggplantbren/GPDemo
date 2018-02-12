import dnest4.classic as dn4
dn4.postprocess()

import matplotlib.pyplot as plt
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")

# Plot some curves through the data
x_data = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0]
y_data = [5.0, 4.8, 4.7, 4.8, 4.9, 5.1, 5.3, 5.2, 5.0,  5.1]
plt.plot(x_data, y_data, "o")

for i in range(0, 10):
    plt.plot(x_data, posterior_sample[i, 2:], color="g", alpha=0.2)

plt.show()

