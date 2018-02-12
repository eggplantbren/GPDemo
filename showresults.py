import dnest4.classic as dn4
dn4.postprocess()

import matplotlib.pyplot as plt
posterior_sample = dn4.my_loadtxt("posterior_sample.txt")

# Plot some curves
for i in range(0, 10):
    plt.plot(posterior_sample[i, 2:], alpha=0.2)

plt.show()

