from bmtk.analyzer.cell_vars import plot_report

plot_report(config_file='simulation_config.json')

import h5py
import matplotlib.pyplot as plt
import numpy as np

f = h5py.File('output/syn_report.h5')
data = [l[0] for l in list(f['data'])]
data = np.abs(data)

plt.plot(data)
plt.ylabel('synaptic current')
plt.show()
 
